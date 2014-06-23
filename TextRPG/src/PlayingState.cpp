#include "GraphicDevice.h"
#include "ConsoleInput.h"
#include "Game.h"
#include "TextGame.h"

#include "Canvas.h"

#include "GameState.h"
#include "PlayingState.h"

PlayingState::PlayingState(void) : GameState("PlayingState")
{
	_lvlIndex = 0;
}

PlayingState::~PlayingState(void)
{
}

void PlayingState::Update(long period)
{
    TextGame* game = TextGame::GetInstance();

	ConsoleInput* input = ConsoleInput::GetInstance();

    if (input->DidVKeyJustGoDown(VK_SPACE))
        NextLevel();
    if (input->DidVKeyJustGoDown(VK_ESCAPE))
        game->ChangeState("WelcomeScreen");

    game->_playerController->Update(period);
    game->_map->Update();
}

void PlayingState::Render()
{
    TextGame* game = TextGame::GetInstance();
    Canvas* canvas = Canvas::GetInstance();
	
	char lvlInfo[100];
	sprintf_s(lvlInfo, 100, "Level : %d", _lvlIndex);
	canvas->ShowText(lvlInfo, vector2i(3, 1), FOREGROUND_WHITE | FOREGROUND_INTENSITY);
    
	// TODO: Don't hard code the map view frame like this
	canvas->DrawBorderDouble(Rect(1, 2, 62, 23), FOREGROUND_WHITE | FOREGROUND_INTENSITY);
	game->_map->Render();

	game->_player->Render();
}

void PlayingState::NextLevel()
{
    TextGame* game = TextGame::GetInstance();
	game->_mapGenerator->Generate(game->_map);
	_lvlIndex++;
}

void PlayingState::Begin(State* preState)
{
	// Don't need to show the cursor while playing
	GraphicDevice::GetInstance()->SetCursorVisibility(false);
}

void PlayingState::End()
{
	// TODO
}