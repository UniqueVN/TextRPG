#include "GraphicDevice.h"
#include "ConsoleInput.h"
#include "Game.h"
#include "TextGame.h"

#include "Canvas.h"

#include "GameState.h"
#include "WelcomeScreen.h"

WelcomeScreen::WelcomeScreen(void) : GameState("WelcomeScreen")
{
	_selectID = 0;

	// Button: Play
	// Button: Exit
}

WelcomeScreen::~WelcomeScreen(void)
{
}

void WelcomeScreen::Update(long period)
{
    TextGame* game = TextGame::GetInstance();

	ConsoleInput* input = ConsoleInput::GetInstance();

	const int MENU_ITEM_COUNT = 2;
	if (input->DidVKeyJustGoDown(VK_UP))
	{
        _selectID--;
		if (_selectID < 0)
			_selectID = MENU_ITEM_COUNT - 1;
	}
	else if (input->DidVKeyJustGoDown(VK_DOWN))
	{
		_selectID++;
		if (_selectID > MENU_ITEM_COUNT - 1)
			_selectID = 0;
	}

	if (input->DidVKeyJustGoDown(VK_RETURN))
	{
		if (_selectID == 0)
			game->ChangeState("PlayingState");
		else if (_selectID == 1)
			game->Exit();
	}

    if (input->DidVKeyJustGoDown(VK_ESCAPE))
        game->Exit();
}

void WelcomeScreen::Render()
{
	// TODO: Import the UI data from the .xml file
	// Just hardcoded the screen for now since we only have 1

	const char* welcomeStr = "TEXT ADVENTURE";
	Canvas* canvas = Canvas::GetInstance();
	Coordinate pos(10, 5);
	vector2i size = canvas->GetTextSize(welcomeStr);
	pos.X = (GraphicDevice::GetInstance()->GetWidth() - size.X) / 2;
	canvas->ShowText(welcomeStr, pos,  FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_WHITE);

	// Play button
	pos.X = 20;
	pos.Y += 5;
	int itemID = 0;
	const char* playBt = "Play game";
	Color color;
	color = (itemID == _selectID) ? (FOREGROUND_WHITE | FOREGROUND_INTENSITY | BACKGROUND_BLUE) : FOREGROUND_WHITE;
	if (itemID == _selectID)
		GraphicDevice::GetInstance()->SetCursorPos(pos);
	canvas->ShowText(playBt, pos, color);
	
	pos.Y += 2;
	itemID++;

	// Exit button
	const char* exitBt = "Exit";
	color = (itemID == _selectID) ? (FOREGROUND_WHITE | FOREGROUND_INTENSITY | BACKGROUND_BLUE) : FOREGROUND_WHITE;
	if (itemID == _selectID)
		GraphicDevice::GetInstance()->SetCursorPos(pos);
	canvas->ShowText(exitBt, pos, color);
}

void WelcomeScreen::Begin(State* preState)
{
	_selectID = 0;
	GraphicDevice::GetInstance()->SetCursorVisibility(true);
}

void WelcomeScreen::End()
{
	// TODO
}