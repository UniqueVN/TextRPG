#include <string>
#include <map>
using namespace std;
#include "State.h"
#include "StateMachine.h"

StateMachine::StateMachine(void) : _curState(0)
{
}

StateMachine::~StateMachine(void)
{
}

State* StateMachine::GetCurrentState()
{
	return _curState;
}

bool StateMachine::ChangeState(const string& stateName)
{
    map<string, State*>::const_iterator iter = _states.find(stateName);
    if (iter == _states.end())
        return false;

	State* nextState = iter->second;

	if (_curState != 0)
		_curState->End();

	nextState->Begin(_curState);
	_curState = nextState;

    return true;
}

bool StateMachine::AddState(const string& stateName, State* state)
{
	_states.insert(pair<string, State*>(stateName, state));
	// TODO: check if there's already a state with same name
	return true;
}

bool StateMachine::AddState(State* state)
{
	_states.insert(pair<string, State*>(state->GetName(), state));
	// TODO: check if there's already a state with same name
	return true;
}