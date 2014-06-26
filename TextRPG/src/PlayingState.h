#pragma once
#include "GameState.h"

class PlayingState : public GameState
{
public:
    PlayingState(void);
    ~PlayingState(void);

    void Update(long);
    void Render();

    void NextLevel();

    void Begin(State* preState = nullptr);
    void End();

protected:
    int _lvlIndex;
};
