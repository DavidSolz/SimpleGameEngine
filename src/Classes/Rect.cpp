#include "Rect.h"

bool Rect::isInBound(const Vector2& _object) {
    return (_object.x >= x && _object.x < x + width &&
        _object.y >= y && _object.y < y + height);
}

bool Rect::isInBound(const Rect& _rect) {
    return (_rect.x >= x && _rect.x + _rect.width < x + width &&
        _rect.y >= y && _rect.y + _rect.height < y + height);
}

bool Rect::isIntersecting(const Rect& _other) {
    return std::fmax(x, _other.x) < std::fmin(x+width, _other.x+_other.width) &&
            std::fmax(y, _other.y) < std::fmin(y+height, _other.y + _other.height);

}
