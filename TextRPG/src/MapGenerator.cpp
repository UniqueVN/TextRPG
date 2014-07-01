#include "BasicTypes.h"
#include "Map.h"
#include "MapGenerator.h"

MapGenerator::MapGenerator(void)
{
}

MapGenerator::~MapGenerator(void)
{
}

void MapGenerator::Generate(Map* map)
{
    _map = map;
    Clear();
}

void MapGenerator::Clear()
{
    Size size = _map->GetSize();
    // Clear the map
    for (int i = 0; i < size.X; i++)
        for (int j = 0; j < size.Y; j++)
        {
            (*_map)[i][j] = EMPTY_TILE;
        }
}