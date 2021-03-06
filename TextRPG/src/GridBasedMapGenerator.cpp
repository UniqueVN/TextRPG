#include <vector>
using namespace std;
#include "Time.h"
#include "Random.h"
#include "BasicTypes.h"
#include "MapGenerator.h"
#include "Map.h"

#include "Sprite.h"
#include "TextGame.h"

#include "GridBasedMapGenerator.h"

GridBasedMapGenerator::GridBasedMapGenerator(void)
{
    // TODO: Port all these data to the config file
    _cellSize.X = 15;
    _cellSize.Y = 10;
    _minSize.X = _minSize.Y = 4;
    _maxRoomCount = 10;
}

GridBasedMapGenerator::~GridBasedMapGenerator(void)
{
}

void GridBasedMapGenerator::Generate(Map* map)
{
    MapGenerator::Generate(map);
    srand((unsigned int)time(0));
    _rooms.clear();
    
    Size size = _map->GetSize();
    int mX = size.X / _cellSize.X;
    int mY = size.Y / _cellSize.Y;
    _hasRoom = new bool*[mX];
    for (int i = 0; i < mX; i++)
    {
        _hasRoom[i] = new bool[mY];
        for (int j = 0; j < mY; j++)
            _hasRoom[i][j] = false;
    }

    // Choose random cells to generate rooms
	int roomCount = rand(_maxRoomCount / 2, _maxRoomCount);
    int x, y;
    for (int i = 0; i < roomCount; i++)
    {
        while (true)
        {
            x = rand() % mX;
            y = rand() % mY;
            if (!_hasRoom[x][y])
                break;
        }
        _hasRoom[x][y] = true;
        GenerateRoom(x, y);
    }

    for (int i = 1; i < roomCount; i++)
    {
        int r1 = rand() % i;
        GenerateHallway(r1, i);
    }

    MakeWall();

    // Put the player into the first room
    Sprite* player = TextGame::GetInstance()->GetPlayer();
    vector2f playerStart;
    playerStart.X = (_rooms[0].Left + _rooms[0].Right) * .5f;
    playerStart.Y = (_rooms[0].Top + _rooms[0].Bottom) * .5f;
    player->SetPosition(playerStart);

    map->UpdateObstacleMap();
}

// Generate a room at cell(x, y)
void GridBasedMapGenerator::GenerateRoom(int x, int y)
{
    Coordinate topLeft;
    topLeft.X = x * _cellSize.X;
    topLeft.Y = y * _cellSize.Y;

    // Choose random size for the room (remember resever at least 2 unit for walls)
    Size roomSize;
    roomSize.X = rand(_minSize.X, _cellSize.X - 2);
    roomSize.Y = rand(_minSize.Y, _cellSize.Y - 2);
    while (roomSize.Y < roomSize.X / 2)
        roomSize.Y++;
    while (roomSize.X < roomSize.Y / 2)
        roomSize.X++;

    Coordinate pos = topLeft + (_cellSize - roomSize) / 2;

    Rect rectRoom;
    rectRoom.Left = pos.X;
    rectRoom.Right = pos.X + roomSize.X;
    rectRoom.Top = pos.Y;
    rectRoom.Bottom = pos.Y + roomSize.Y;
    _rooms.push_back(rectRoom);

    for (int i = pos.X; i < pos.X + roomSize.X; i++)
        for (int j = pos.Y; j < pos.Y + roomSize.Y; j++)
            (*_map)[i][j] = ROOM_TILE;
}

// Generate a HALLWAY_TILE between 2 room
void GridBasedMapGenerator::GenerateHallway(int r1, int r2)
{
    Rect room1 = _rooms[r1];
    Coordinate center1;
    center1.X = (room1.Left + room1.Right) / 2;
    center1.Y = (room1.Top + room1.Bottom) / 2;
    Size size1(room1.Right - room1.Left, room1.Bottom - room1.Top);

    Rect room2 = _rooms[r2];
    Coordinate center2;
    center2.X = (room2.Left + room2.Right) / 2;
    center2.Y = (room2.Top + room2.Bottom) / 2;
    Size size2(room2.Right - room2.Left, room2.Bottom - room2.Top);
    
    Coordinate turnPoint;
    turnPoint.X = center2.X;    // Same column as room 2
    turnPoint.Y = center1.Y;    // Same row as room 1

    if ((*_map)[turnPoint.X][turnPoint.Y] == EMPTY_TILE)
        (*_map)[turnPoint.X][turnPoint.Y] = HALLWAY_TILE;
    // Draw a horizon HALLWAY_TILE from room 1 to turn point
    int dir = (center1.X < turnPoint.X) ? 1 : -1;
    if (center1.X != turnPoint.X)
    for (int x = turnPoint.X - dir; x != center1.X; x -= dir)
    {
        if ((*_map)[x][turnPoint.Y] == EMPTY_TILE)
            (*_map)[x][turnPoint.Y] = HALLWAY_TILE;
        //else if ((*_map)[x][turnPoint.Y] == HALLWAY_TILE)
        //    continue;
    }

    // Draw a vertical HALLWAY_TILE from room 2 to turn point 
    dir = (center2.Y < turnPoint.Y) ? 1 : -1;
    if (center2.Y != turnPoint.Y)
    for (int y = turnPoint.Y - dir; y != center2.Y; y -= dir)
    {
        if ((*_map)[turnPoint.X][y] == EMPTY_TILE)
            (*_map)[turnPoint.X][y] = HALLWAY_TILE;
        //else if ((*_map)[turnPoint.X][y] == HALLWAY_TILE)
        //    break;
    }
}

void GridBasedMapGenerator::MakeWall()
{
    const char VERTICAL_WALL = (char)179;
    const char HORIZON_WALL = (char)196;
    //const char WALL = (char)35;
	const char WALL = (char)177;

    // North, East, South, West, NorthWest, NorthEast, SouthWest, SouthEast
    const vector2i DIR[] = { vector2i(0, -1), vector2i(1, 0), vector2i(0, 1), vector2i(-1, 0), 
                             vector2i(-1, -1), vector2i(1, -1), vector2i(-1, 1), vector2i(1, 1)};
    enum Direction
    {
        North = 1,
        East = 2,
        South = 4, 
        West = 8
    };

    Coordinate pos;
    //for (uint i = 0; i < _rooms.size(); i++)
    //{
    //    Rect room = _rooms[i];
    //    for (int x = room.Left; x < room.Right; x++)
    //    {
    //        pos.X = x;
    //        for (int y = room.Top; y < room.Bottom; y++)
    //        {
    //            pos.Y = y;
    //            // Check 8 direction
    //            for (int d = 0; d < 8; d++)
    //                if ((*_map)[pos + DIR[d]] == EMPTY_TILE)
    //                {
    //                    (*_map)[pos + DIR[d]] = WALL;
    //                }
    //        }
    //    }
    //}

    //int next = 0;
    //Size mapSize = _map->GetSize();
    //vector2i pos;
    //for (int i = 0; i < mapSize.X - 1; i++)
    //{
    //    pos.X = i;
    //    for (int j = 0; j < mapSize.Y - 1; j++)
    //    {
    //        pos.Y = j;

    //        if ((*_map)[pos] != ' ')
    //            continue;

    //        // Check 8 direction
    //        for (int d = 0; d < 8; d++)
    //            //if (((*_map)[pos + DIR[d]] != ' ') && ((*_map)[pos + DIR[d]] != WALL))
    //            if ((*_map)[pos + DIR[d]] != '.')
    //            {
    //                (*_map)[pos] = WALL;
    //            }

    //        //// Check 4 direction
    //        //for (int d = 0; d < 4; d++)
    //        //    if ((*_map)[pos + DIR[d]] != ' ')
    //        //        next |= (1 << d);

    //        //if ((next == North) || (next == South))
    //        //    (*_map)[pos] = HORIZON_WALL;
    //        //else if ((next == West) || (next == East))
    //        //    (*_map)[pos] = VERTICAL_WALL;
    //        //else if ((next == West) || (next == East))
    //        //    (*_map)[pos] = VERTICAL_WALL;
    //    }       
    //}
}
