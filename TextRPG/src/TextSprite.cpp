#include "BasicTypes.h"
#include "GraphicDevice.h"
#include "TextGame.h"
#include "ViewFrame.h"
#include "Map.h"
#include "TextSprite.h"

TextSprite::TextSprite(void) : Sprite()
{
}

TextSprite::TextSprite(TextSprite* other) : Sprite(other)
{
}

TextSprite::~TextSprite(void)
{
}

void TextSprite::Init()
{
	Sprite::Init();
	// TODO
}

void TextSprite::Update(long deltaTime)
{
	// TODO
}

void TextSprite::Render()
{
    Map* map = TextGame::GetInstance()->GetMap();
    vector2f offset = map->MapPositionToScreen(_pos);

    GraphicDevice* device = GraphicDevice::GetInstance();
	device->SetPixelData((int)offset.X, (int)offset.Y, _avatar, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
}

void TextSprite::Move(const vector2f& dir)
{
    vector2f newPos = _pos + dir;
    Map* map = TextGame::GetInstance()->GetMap();

    // Only move if the cell is empty
    if (map->IsCellEmpty((int)newPos.X, (int)newPos.Y))
    {
        _pos = newPos;
    }
}