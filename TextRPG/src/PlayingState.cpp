#include "GraphicDevice.h"
#include "ConsoleInput.h"
#include "Game.h"
#include "TextGame.h"

#include "ViewFrame.h"
#include "Map.h"

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
        game->ChangeState("MenuState");

    game->_playerController->Update(period);
    game->_map->Update();
}

void PlayingState::Render()
{
    TextGame* game = TextGame::GetInstance();
    Canvas* canvas = Canvas::GetInstance();
	
	// TODO: Don't hard code the map view frame like this
    ViewFrame* viewFrame = game->_map->GetViewFrame();
    vector2f framePos = viewFrame->GetPosition();
    vector2f frameSize = viewFrame->GetSize();
    canvas->DrawBorderDouble(Rect(framePos.X - 1, framePos.Y - 1, frameSize.X + 1, frameSize.Y + 1), FOREGROUND_WHITE | FOREGROUND_INTENSITY);
	game->_map->Render();

	char lvlInfo[100];
	sprintf_s(lvlInfo, 100, "Level : %d", _lvlIndex);
    vector2i mapInfoPos(framePos.X + frameSize.X + 2, framePos.Y);
    canvas->ShowText(lvlInfo, mapInfoPos, FOREGROUND_WHITE | FOREGROUND_INTENSITY);
    
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