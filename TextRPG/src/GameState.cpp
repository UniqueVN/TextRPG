#include <string>
using namespace std;
#include "State.h"
#include "GameState.h"

GameState::GameState(void)
{
}

GameState::GameState(const string& name) : State(name)
{
}

GameState::~GameState(void)
{
}