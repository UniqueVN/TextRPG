#include <windows.h>
#include "stdio.h"

#include "BasicTypes.h"
#include "GraphicDevice.h"

#include "Game.h"
#include "TextGame.h"

#include "Map.h"
#include "MapGenerator.h"
#include "GridBasedMapGenerator.h"

const int COLUMNS_COUNT = 80;
const int ROWS_COUNT = 50;

void TestGraphicDevice();
void TestMap();

int main()
{
    system("cls");

    Game* game = TextGame::GetInstance();
    game->Run();

    game->Destroy();
    TextGame::DeleteInstance();

    return 0;
}

void TestGraphicDevice()
{
    GraphicDevice::CreateInstance(Size(COLUMNS_COUNT, ROWS_COUNT));
    
    GraphicDevice* graphicDevice = GraphicDevice::GetInstance();
    graphicDevice->Clear();
    
    Coordinate pos;
    int t = 0;
    for (int i = 0; i < COLUMNS_COUNT; i++)
    {
        pos.X = i;
        for (int j = 0; j < ROWS_COUNT; j++)
        {
            pos.Y = j;
            (*graphicDevice)[pos].Char.AsciiChar = t++;
            (*graphicDevice)[pos].Attributes = rand() % 256;
        }
    }

    Rect rect;
    rect.Top = 16;
    rect.Bottom = 18;
    rect.Left = 20;
    rect.Right = 60;
    Color color = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    graphicDevice->DrawRectangle(rect, color, (char)179);
}

void TestMap()
{
    GraphicDevice::GetInstance()->Clear();

    //Size mapSize(80, 50);
    Size mapSize(80, 30);
    Map* map = new Map(mapSize);

    MapGenerator* generator = new GridBasedMapGenerator();
    generator->Generate(map);
    
    map->Render();
}