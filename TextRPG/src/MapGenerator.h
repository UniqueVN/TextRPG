#pragma once
#include "BasicTypes.h"

class Map;
class MapGenerator
{
public:
    MapGenerator(void);
    ~MapGenerator(void);

    virtual void Generate(Map*);
protected:
    void Clear();

    Map* _map;
};
