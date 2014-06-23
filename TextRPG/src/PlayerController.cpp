#include "Vector2.h"
#include "ConsoleInput.h"
#include "Sprite.h"
#include "TextSprite.h"
#include "PlayerController.h"

PlayerController::PlayerController(void) : _puppet(0), _speed(1), _moveTime(0)
{
}

PlayerController::~PlayerController(void)
{
}

void PlayerController::Update(long period)
{
    ConsoleInput* input = ConsoleInput::GetInstance();

    if (_puppet == 0)
        return;

	_movePeriod = int(1000 / _speed);
    _moveTime += period;

	// TODO: Make the input system send out input event and listen to it
	// Update the player's movements base on the input keys
    if (input->DidVKeyJustGoDown(VK_UP))
        Move(D_Up);
    else if (input->DidVKeyJustGoDown(VK_DOWN))
        Move(D_Down);
    else if (input->DidVKeyJustGoDown(VK_LEFT))
        Move(D_Left);
    else if (input->DidVKeyJustGoDown(VK_RIGHT))
        Move(D_Right);
    else if (_moveTime >= _movePeriod)
    {
        _moveTime = 0;
        // Move player if the movement keys still down
        if (input->IsVKeyDown(VK_UP)) 
            Move(D_Up);
        if (input->IsVKeyDown(VK_DOWN))
            Move(D_Down);
        if (input->IsVKeyDown(VK_LEFT))
            Move(D_Left);
        if (input->IsVKeyDown(VK_RIGHT))
            Move(D_Right);
    }
}

float PlayerController::GetSpeed()
{
	return _speed;
}

void PlayerController::SetSpeed(const float& newSpeed)
{
	_speed = newSpeed;
}

void PlayerController::Move(const MovementDirection& dir)
{
	_puppet->Move(DIR_MOVEMENT[dir]);
}

Sprite* PlayerController::GetPuppet()
{
    return _puppet;
}

void PlayerController::SetPuppet(Sprite* sprite)
{
    _puppet = sprite;
}
