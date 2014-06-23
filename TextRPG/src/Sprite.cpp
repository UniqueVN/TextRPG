#include "Vector2.h"
#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::Sprite(Sprite* other) : _pos(other->_pos), _size(other->_size), _isAlive(true)
{
    Init();
}

Sprite::~Sprite(void)
{
}

void Sprite::Init()
{
	// TODO
}

void Sprite::Move(const vector2f& dir)
{
    _pos += dir;
}