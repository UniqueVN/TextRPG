#include <windows.h>
#include <assert.h>
#include "ConsoleInput.h"

ConsoleInput::ConsoleInput(void)
{
    _curState = 0;
    for (int i = 0; i < 256; i++)
    {
        _keyState[0][i] = false;
        _keyState[1][i] = false;
    }
    
    Init();
}

ConsoleInput::~ConsoleInput(void)
{
}

void ConsoleInput::Update()
{
    _curState = 1 - _curState;
    for (int i = 0; i < 256; i++)
        _keyState[_curState][i] = _keyState[1 - _curState][i];

    // Get the number of input events in buffer
    //WORD numInputEvent;
    //GetNumberOfConsoleInputEvents(_hInput, &numInputEvent);

    // Read in the player's input
	INPUT_RECORD inputRecord[128];
	DWORD eventsReadIn;
	ReadConsoleInput(_hInput, inputRecord, 128, &eventsReadIn);

    int vKey;
    for (int i = 0; i < (int)eventsReadIn; i++)
    {
        switch (inputRecord[i].EventType)
        {
        case KEY_EVENT:
            vKey = inputRecord[i].Event.KeyEvent.wVirtualKeyCode;
            _keyState[_curState][vKey] = (inputRecord[i].Event.KeyEvent.bKeyDown != 0);
            break;
        case MOUSE_EVENT:
            // TODO
            //int vKey = inputRecord[i].Event.MouseEvent.;
            //_keyState[vKey] = inputRecord[i].Event.KeyEvent.bKeyDown;
            break;
        default:
            break;
        }
    }

    FlushConsoleInputBuffer(_hInput);
}

void ConsoleInput::Init()
{
    _hInput = GetStdHandle(STD_INPUT_HANDLE);
}

bool ConsoleInput::IsVKeyDown(int vKey) const
{
	assert( vKey >= 0 && vKey < 256);
	return _keyState[_curState][vKey];
}

bool ConsoleInput::DidVKeyJustGoDown(int vKey) const
{
	assert( vKey >= 0 && vKey < 256);
	// This key is down and last time it's up
	return (_keyState[_curState][vKey]) && (!_keyState[1 - _curState][vKey]);
}
bool ConsoleInput::DidVKeyJustGoUp(int vKey) const
{
	assert( vKey >= 0 && vKey < 256);
	// This key is up and last time it's down
	return (!_keyState[_curState][vKey]) && (_keyState[1 - _curState][vKey]);
}