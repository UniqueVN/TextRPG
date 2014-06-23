#pragma once
#include "GameState.h"

class WelcomeScreen : public GameState
{
public:
    WelcomeScreen(void);
    ~WelcomeScreen(void);

	void Update(long);
    void Render();

	void Begin(State* preState = NULL);
	void End();

protected:
	int _selectID;
};
