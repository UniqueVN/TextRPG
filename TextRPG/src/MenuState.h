#pragma once
#include "GameState.h"

class MenuState : public GameState
{
public:
    MenuState(void);
    ~MenuState(void);

	void Update(long);
    void Render();

	void Begin(State* preState = NULL);
	void End();

protected:
	int _selectID;
};