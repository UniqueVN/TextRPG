#include "Level.h"

Level::Level(void)
{
}

Level::~Level(void)
{
}

void Level::Start()
{
}

bool Level::IsFinished()
{
	// TODO
	return false;
}

int Level::GetIndex()
{
	return _index;
}

void Level::SetIndex(int index)
{
	_index = index;
}

Map* Level::GetMap()
{
	return _map;
}

void Level::SetMap(Map* map)
{
	_map = map;
}
