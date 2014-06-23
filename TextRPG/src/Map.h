#pragma once
#include "BasicTypes.h"

class ViewFrame;

class Map
{
public:
    Map(const Size& size);
    ~Map(void);

    void Update();
    void Render();

    void SetSize(const Size&);
    Size GetSize();

    ViewFrame* GetViewFrame();
    vector2f GetOffset();
    vector2f MapPositionToScreen(const vector2f& mapPos);

    void UpdateObstacleMap();
    bool IsCellEmpty(const vector2i& cell);
    bool IsCellEmpty(int x, int y);

    TileID& operator [](const Coordinate&);
    TileID* operator [](const int&);
protected:
    void Init();

    Size _size;
    TileID** _tiles;
    char** _obstacles;

    ViewFrame* _viewFrame;
    vector2f _scrOffset;
};