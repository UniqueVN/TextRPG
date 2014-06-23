#pragma once
#include <string>
using namespace std;
#include "State.h"

class GameState : public State
{
public:
    GameState(void);
    GameState(const string& name);
    ~GameState(void);

    virtual void Update(long) = 0;
    virtual void Render() = 0;
};
