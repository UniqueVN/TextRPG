#pragma once
#include <list>
using namespace std;
#include "Map.h"
#include "Sprite.h"

class Level
{
public:
    Level(void);
    ~Level(void);

	virtual void Start();
    virtual bool IsFinished();

	int GetIndex();
	void SetIndex(int);

	Map* GetMap();
	void SetMap(Map*);

protected:
    int _index;

	Map* _map;

	list<Sprite*> _sprites;	// All the sprites currently in the levels
};
