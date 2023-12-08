#ifndef GLYPHREADER_H
#define GLYPHREADER_H

#include <fstream>
#include <string>
#include <cstdint>
#include <vector>
#include <map>

#ifdef __APPLE__
    #include <OpenGL/gl.h>
#else
    #include <GL/gl.h>
#endif

//TODO

struct{
    uint32_t scalerType;
    uint16_t numTables;
    uint16_t searchRange;
    uint16_t entrySelector;
    uint16_t rangeShift;
} offsetSubtable;

struct table{
    uint32_t tag;
    uint32_t checksum;
    uint32_t offset;
    uint32_t length;
};

struct glyf{
    int16_t numberOfContours;
    int16_t xMin;
    int16_t yMin;
    int16_t xMax;
    int16_t yMax;
};

struct{
    uint32_t version;
    uint32_t fontRevision;
    uint32_t checksumAdjustment;
    uint32_t magicNumber;
    uint16_t flags;
    uint16_t unitsPerEm;
    uint64_t created;
    uint64_t modified;
    int16_t xMin;
    int16_t yMin;
    int16_t xMax;
    int16_t yMax;
    uint16_t macStyle;
    uint16_t lowestRecPPEM;
    int16_t fontDirectionHint;
    int16_t indexToLocFormat;
    int16_t glyphDataFormat;
} head;

struct {
    float version;
    uint16_t numGlyphs;
    uint16_t maxPoints;
    uint16_t maxContours;
    uint16_t maxComposePoints;
    uint16_t maxComposeContours;
    uint16_t maxZones;
    uint16_t maxTwilightPoints;
    uint16_t maxStorage;
    uint16_t maxFunctionDefs;
    uint16_t maxInstructionDefs;
    uint16_t maxStackElements;
    uint16_t maxSizeOfInstructions;
    uint16_t maxComponentElements;
    uint16_t maxComponentDepth;
} maxp;

struct {
    float version;
    int16_t ascent;
    int16_t descent;
    int16_t lineGap;
    uint16_t advanceWidthMax;
    int16_t minLeftSideBearing;
    int16_t minRightSideBearing;
    int16_t xMaxExtent;
    int16_t caretSlopeRise;
    int16_t caretSlopeRun;
    int16_t caretOffset;
    int32_t reserved; //Not in use
    int16_t metricDataFormat;
    uint16_t numOfLongHorMetrics;
} hhea;

struct{
    uint32_t * offsets;
}loca;

struct encodingRecord{
    uint16_t platformID;
    uint16_t encodingID;
    uint32_t offset;
};

struct{
    uint16_t version;
    uint16_t numTables;
    encodingRecord * records;
    //map here
}cmap;

struct hMetrics{
    uint16_t advanceWidth;
    int16_t leftSideBearing;
};

struct {
    hMetrics * metrics;
    int16_t * leftSideBearing;
} hmtx;

struct Glyph {
    GLuint textureID;      // Texture ID
    uint32_t width;        // Width of glyph
    uint32_t height;       // Height of glyph
    uint32_t bearingX;     // Bearing X
    uint32_t bearingY;     // Bearing Y
    uint32_t advance;      // Offset to next glyph
};

class GlyphReader {

public:
    GlyphReader(const std::string &filepath);

    void ReadData();

    ~GlyphReader();

private:

    void ParseTable(char *_target, const std::string &tableName);
    uint32_t GetTableOffset(const std::string &tableName);
    uint32_t CalcTableChecksum(uint32_t *table, uint32_t numberOfBytesInTable);
    table* GetTable(const std::string &tableName);

    uint32_t ReverseBytes32(const uint32_t &value);
    uint16_t ReverseBytes16(const uint16_t &value);
    int32_t ReverseBytes32Signed(const int32_t &value);
    int16_t ReverseBytes16Signed(const int16_t &value);


    std::map<std::string,uint32_t> stringToTag = {
        {"head" , 0x68656164},
        {"maxp" , 0x6D617870},
        {"loca", 0x6C6F6361},
        {"hhea", 0x68686561},
        {"hmtx" , 0x686D7478},
        {"glyf" , 0x676C7966},
        {"cmap", 0x636D6170}
    };

    glyf* glyfs;
    std::map<uint32_t, table> tables;
    std::ifstream input;
};

#endif
