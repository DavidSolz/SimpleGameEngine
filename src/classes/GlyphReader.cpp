#include "GlyphReader.h"


GlyphReader::GlyphReader(const std::string &filepath){
    //Open file in binary mode
    input.open(filepath, std::ios::binary | std::ios::in);

    //Check if file is opened
    if(!input.is_open()){
        fprintf(stderr, "File can't be opened\n");
        exit(-1);
    }
}

uint32_t GlyphReader::ReverseBytes32(const uint32_t &value){
    return ((value >> 24) & 0xFF) | ((value >> 8) & 0xFF00) | ((value << 8) & 0xFF0000) | ((value << 24) & 0xFF000000);
}
uint16_t GlyphReader::ReverseBytes16(const uint16_t &value){
    return (value >> 8 & 0xFF) | (value << 8 & 0xFF00);
}

int32_t GlyphReader::ReverseBytes32Signed(const int32_t &value){
    return ((value >> 24) & 0xFF) | ((value >> 8) & 0xFF00) | ((value << 8) & 0xFF0000) | ((value << 24) & 0xFF000000);
}

int16_t GlyphReader::ReverseBytes16Signed(const int16_t &value){
    return (value >> 8 & 0xFF) | (value << 8 & 0xFF00);
}


void GlyphReader::ReadData(){
    // Read offsetSubtable
    input.read((char*)(&offsetSubtable), 12); 

    offsetSubtable.numTables = ReverseBytes16(offsetSubtable.numTables);

    // Read tables directory
    table _table;
    for(uint16_t index=0; index < offsetSubtable.numTables; index++){
        input.read((char*)&_table, sizeof(table));

        _table.tag = ReverseBytes32(_table.tag);
        _table.checksum = ReverseBytes32(_table.checksum);
        _table.offset = ReverseBytes32(_table.offset);
        _table.length = ReverseBytes32(_table.length);

        tables[_table.tag] = _table;
    } 

    //Parse some important data
    ParseTable((char*)(&head), "head");
    ParseTable((char*)(&maxp), "maxp");
    ParseTable((char*)(&hhea), "hhea");

    //Reverse needed data
    head.indexToLocFormat = 1; //ReverseBytes16Signed(head.indexToLocFormat); TODO
    head.checksumAdjustment = ReverseBytes32(head.checksumAdjustment);
    head.unitsPerEm = ReverseBytes32(head.unitsPerEm);
    maxp.numGlyphs = ReverseBytes16(maxp.numGlyphs);
    hhea.numOfLongHorMetrics = ReverseBytes16(hhea.numOfLongHorMetrics);

    //Allocate memory for hmtx
    hmtx.metrics = new hMetrics[hhea.numOfLongHorMetrics];
    hmtx.leftSideBearing = new int16_t[maxp.numGlyphs - hhea.numOfLongHorMetrics];


    //Move cursor to hmtx data
    input.seekg(GetTableOffset("hmtx"));

    //Read hmtx data
    input.read((char*)(hmtx.metrics), hhea.numOfLongHorMetrics * 4);
    input.read((char*)(hmtx.leftSideBearing), (maxp.numGlyphs - hhea.numOfLongHorMetrics) * 2);

    for(uint16_t index=0; index<hhea.numOfLongHorMetrics; index++){
        hMetrics* metric = hmtx.metrics+index;
        metric->advanceWidth = ReverseBytes16(metric->advanceWidth);
        metric->leftSideBearing = ReverseBytes16Signed(metric->leftSideBearing);
    }

    //Allocate memory for loca
    loca.offsets = new uint32_t[maxp.numGlyphs+1];

    //Move cursor to loca data
    input.seekg(GetTableOffset("loca"));

    uint16_t recordSize = head.indexToLocFormat==0 ? 2 : 4;
   
    //Read loca data
    input.read((char*)(loca.offsets), (maxp.numGlyphs + 1) * 2);
    
    for(uint16_t index=0; index < maxp.numGlyphs + 1 ; index++){
        loca.offsets[index] = ReverseBytes32(loca.offsets[index]);
    }

    // Allocate memory for glyfs
    glyfs = new glyf[maxp.numGlyphs];
    uint16_t multiplier = head.indexToLocFormat == 0 ? 2 : 1;

    uint32_t tableOffset = GetTableOffset("glyf");

    for(uint16_t index = 0; index < maxp.numGlyphs; index++){
        uint32_t locaOffset = loca.offsets[index] * multiplier;

        input.seekg(tableOffset + locaOffset);
        input.read((char*)(glyfs+index), 10);

        glyfs[index].numberOfContours = ReverseBytes16(glyfs[index].numberOfContours);
        glyfs[index].xMax = ReverseBytes16(glyfs[index].xMax);
        glyfs[index].yMax = ReverseBytes16(glyfs[index].yMax);
        glyfs[index].xMin = ReverseBytes16(glyfs[index].xMin);
        glyfs[index].yMin = ReverseBytes16(glyfs[index].yMin);
    }

    //Move cursor to cmap data
    input.seekg(GetTableOffset("cmap"));

    //Read first 4 bytes
    input.read((char*)(&cmap), 4);

    cmap.version = ReverseBytes16(cmap.version);
    cmap.numTables = ReverseBytes16(cmap.numTables);

    //Check cmap version
    if(cmap.version!=0){
        fprintf(stderr, "cmap version should be 0 but is %d\n", cmap.version);  
        exit(-1);
    }

    //Allocate memory for cmap
    cmap.records = new encodingRecord[cmap.numTables];

    for(uint16_t index = 0; index < cmap.numTables; index++){
        encodingRecord * record = cmap.records+index;
        input.read((char*)record, 8);
        record->platformID = ReverseBytes16(record->encodingID);
        record->encodingID = ReverseBytes16(record->encodingID);
        record->offset = ReverseBytes32(record->offset);
    }

    int32_t selectedOffset = -1;
    for(uint32_t index = 0; index< cmap.numTables; index++){
        encodingRecord * record = cmap.records+index;

        bool isWindowsPlatform = record->platformID==3 && 
        (record->encodingID<2 || record->encodingID==10);

        bool isUnicodePlatform = record->platformID==0 &&(record->encodingID<5);

        if(isWindowsPlatform || isUnicodePlatform){
            selectedOffset = record->offset;
            break;
        }
    }

    if(selectedOffset==-1){
        fprintf(stderr, "Font does not contain any recognized platform and encoding.\n");
        exit(-1);
    }

    input.seekg(selectedOffset);

    uint16_t format;
    input.read((char*)&format, 2);
    if(format!=4){
        fprintf(stderr, "Unsupported font format : %X. Required 4.\n", format); //It throws an error, reading issue ?
        exit(-1);
    }

    //TODO character mapping and textures also there is an issue with loc value
}

uint32_t GlyphReader::GetTableOffset(const std::string &tableName){

    table *_table = GetTable(tableName);

    return _table->offset;
}

table* GlyphReader::GetTable(const std::string &tableName){

    uint32_t tag = stringToTag[tableName];
    //Check if table with that name exits
    if(tables.find(tag)==tables.end()){
        fprintf(stderr, "%s can't be found.\n", tableName.c_str());
        exit(-1);
    }

    return &tables[tag];
}

uint32_t GlyphReader::CalcTableChecksum(uint32_t *table, uint32_t numberOfBytesInTable){
    uint32_t sum = 0;
    uint32_t length = (numberOfBytesInTable + 3)>>2;
    while(length-->0)
        sum += *table++;
    return sum;
}

void GlyphReader::ParseTable(char *_target, const std::string &tableName){
    
    //Assign directory table
    table *directoryTable = GetTable(tableName);
    
    //Set position in file
    input.seekg(directoryTable->offset);

    //Read data from stream to provided _object
    input.read(_target, directoryTable->length);

}

GlyphReader::~GlyphReader(){
    //Close file if it is open
    if(input.is_open())
        input.close();
    
    //Release memory
    delete[] glyfs;
    delete[] cmap.records;
    delete[] loca.offsets;
    delete[] hmtx.metrics;
    delete[] hmtx.leftSideBearing;
}