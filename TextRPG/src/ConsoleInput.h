#pragma once
#include <windows.h>
#include "Singleton.h"

class ConsoleInput : public Singleton<ConsoleInput>
{
public:
    void Update();

	// Check the states of virtual keys
	bool IsVKeyDown(int vKey) const;
	bool DidVKeyJustGoDown(int vKey) const;
	bool DidVKeyJustGoUp(int vKey) const;
protected:
    friend class Singleton<ConsoleInput>;
    ConsoleInput(void);
    ~ConsoleInput(void);

    void Init();

    HANDLE _hInput;

	bool _keyState[2][256];	// Two array: one for previous state, one for current state
	int _curState;					// Index of current state
};
