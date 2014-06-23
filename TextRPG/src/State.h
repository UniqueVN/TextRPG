#pragma once
#include <string>
using namespace std;

class State
{
public:
	State(void);
	State(const string& name);
	~State(void);

	virtual void Begin(State* preState = 0) = 0;
	virtual void End() = 0;

	string GetName();
	void SetName(const string&);

protected:
	string _name;
};
