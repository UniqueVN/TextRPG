#pragma once
#include <map>
using namespace std;

class State;

class StateMachine
{
public:
    StateMachine(void);
    ~StateMachine(void);

    State* GetCurrentState();
    bool ChangeState(const string&);
    bool AddState(const string&, State*);
    bool AddState(State*);

protected:
    State* _curState;
    map<string, State*> _states;
};
