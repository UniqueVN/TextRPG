#pragma once
#include <vector>
using namespace std;
#include "BasicTypes.h"
#include "MapGenerator.h"

class Map;

class GridBasedMapGenerator : public MapGenerator
{
public:
    GridBasedMapGenerator(void);
    ~GridBasedMapGenerator(void);

    void Generate(Map*);

protected:
    void GenerateRoom(int x, int y);    // Generate a room at cell(x, y)
    void GenerateHallway(int r1, int r2);   // Generate a hallway between 2 room
    void MakeWall();

    Size _cellSize;
    Size _minSize;
    int _maxRoomCount;
    bool** _hasRoom;
    vector<Rect> _rooms;
};