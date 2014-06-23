#include <string>
using namespace std;
#include "State.h"

State::State(void)
{
}

State::State(const string& name) : _name(name)
{
}

State::~State(void)
{
}

string State::GetName()
{
	return _name;
}

void State::SetName(const string& name)
{
	_name = name;
}
