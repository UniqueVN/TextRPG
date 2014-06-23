#include "BasicTypes.h"
#include "GraphicDevice.h"
#include "ViewFrame.h"

#include "TextGame.h"
#include "Sprite.h"

#include "Map.h"

Map::Map(const Size& size) : _size(size), _scrOffset(0, 0)
{
    _tiles = 0;
    Init();
}

Map::~Map(void)
{
}

void Map::Init()
{
    _viewFrame = new ViewFrame();

    _tiles = new TileID*[_size.X];
    _obstacles = new char*[_size.X];
    for (int i = 0; i < _size.X; i++)
    {
        _tiles[i] = new TileID[_size.Y];
        _obstacles[i] = new char[_size.Y];
    }
}

void Map::UpdateObstacleMap()
{
    for (int i = 0; i < _size.X; i++)
        for (int j = 0; j < _size.Y; j++)
        {
            if ((_tiles[i][j] == HALLWAY_TILE) || (_tiles[i][j] == ROOM_TILE))
                _obstacles[i][j] = 0;
            else
                _obstacles[i][j] = 1;
        }
}

void Map::Update()
{
    Sprite* player = TextGame::GetInstance()->GetPlayer();
    _viewFrame->ComputeOffset(this, player->GetPosition());
    _scrOffset = _viewFrame->GetOffset() - _viewFrame->GetPosition();
}

void Map::Render()
{
    GraphicDevice* GraphicDevice = GraphicDevice::GetInstance();
    vector2f viewSize = _viewFrame->GetSize();
    vector2f offset = _viewFrame->GetOffset();
    vector2f pos = _viewFrame->GetPosition();

    Coordinate scrPos;
    int x0 = (int)offset.X;
    int x1 = x0 + (int)viewSize.X;
    int y0 = (int)offset.Y;
    int y1 = y0 + (int)viewSize.Y;
    for (int i = x0; i < x1; i++)
    {
        scrPos.X = (int)pos.X + i - x0;
        for (int j = y0; j < y1; j++)
        {
            scrPos.Y = (int)pos.Y + j - y0;
            (*GraphicDevice)[scrPos].Char.AsciiChar = _tiles[i][j];
        }
    }
}   

void Map::SetSize(const Size& newSize)
{
    _size = newSize;
    Init();
}

Size Map::GetSize()
{
    return _size;
}

ViewFrame* Map::GetViewFrame()
{
    return _viewFrame;
}

vector2f Map::GetOffset()
{
    return _viewFrame->GetOffset();
}

vector2f Map::MapPositionToScreen(const vector2f& mapPos)
{
    return (mapPos - _scrOffset);
}

TileID& Map::operator [](const Coordinate& coord)
{
    return _tiles[coord.X][coord.Y];
}

TileID* Map::operator [](const int& index)
{
    return _tiles[index];
}

bool Map::IsCellEmpty(const vector2i& cell)
{
    if ((cell.X < 0) || (cell.X > _size.X) || (cell.Y < 0) || (cell.Y > _size.Y))
        return false;
    return (_obstacles[cell.X][cell.Y] == 0);
}

bool Map::IsCellEmpty(int x, int y)
{
    if ((x < 0) || (x > _size.X) || (y < 0) || (y > _size.Y))
        return false;
    return (_obstacles[x][y] == 0);
}