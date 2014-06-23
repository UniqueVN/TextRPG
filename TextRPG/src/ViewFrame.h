#pragma once
#include "BasicTypes.h"
#include "Vector2.h"

class Map;

class ViewFrame
{
public:
    ViewFrame(void);
    ~ViewFrame(void);

    void ComputeOffset(Map*, const vector2f& focus);

    vector2f GetOffset() { return _offset; }
    vector2f GetSize() { return _size; }
    void SetSize(const vector2f& size) { _size = size; }
    vector2f GetPosition() { return _pos; }
    void SetPosition(const vector2f& pos) { _pos = pos; }

protected:
    vector2f _pos, _size, _offset;
};
