#include "BasicTypes.h"
#include "Vector2.h"
#include "Map.h"

#include "ViewFrame.h"

ViewFrame::ViewFrame(void) : _offset()
{
}

ViewFrame::~ViewFrame(void)
{
}

void ViewFrame::ComputeOffset(Map* map, const vector2f& focus)
{
    // Try to make the focus point in the center of the map
    Size mapSize = map->GetSize();

    vector2f newOffset  = focus - (_size * .5f);
    if (newOffset.X + _size.X > mapSize.X)
        newOffset.X = mapSize.X - _size.X;
    if (newOffset.X < 0)
        newOffset.X = 0.f;
    if (newOffset.Y + _size.Y > mapSize.Y)
        newOffset.Y = mapSize.Y - _size.Y;
    if (newOffset.Y < 0)
        newOffset.Y = 0.f;

    _offset = newOffset;
}