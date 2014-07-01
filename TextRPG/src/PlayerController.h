#pragma once
#include "Sprite.h"
#include "Vector2.h"

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
