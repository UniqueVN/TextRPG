#pragma once
#include "Sprite.h"
#include "Vector2.h"

const vector2f DIR_MOVEMENT[] = { vector2f(1, 0), vector2f(0, 1), vector2f(-1, 0), vector2f(0, -1)};
enum MovementDirection
{
    D_Right = 0,
    D_Down,
    D_Left,
    D_Up
};

class PlayerController
{
public:
    PlayerController(void);
    ~PlayerController(void);

    void Update(long);

    Sprite* GetPuppet();
    void SetPuppet(Sprite*);

	float GetSpeed();
	void SetSpeed(const float& newSpeed);

	void Move(const MovementDirection& dir);

protected:
    Sprite* _puppet;    // Controlled sprite
	float _speed;
	int _movePeriod, _moveTime;
};
