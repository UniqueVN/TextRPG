#include "GraphicDevice.h"
#include "ConsoleInput.h"
#include "Game.h"
#include "TextGame.h"

#include "Canvas.h"

#include "UIScreen.h"
#include "MainScreen.h"

MainScreen::MainScreen(UIComponent* parent) : UIScreen(parent)
{
}

MainScreen::~MainScreen(void)
{
}

void MainScreen::Update(long period)
{
    UIComponent::Update(period);

    TextGame* game = TextGame::GetInstance();

	ConsoleInput* input = ConsoleInput::GetInstance();

    // TODO: Pass the input to the child component and listen to event onClick on the button in the menu
    // For now, just make sure player get into the game if he hit Enter and quit and hit Escape so the game still playable
	if (input->DidVKeyJustGoDown(VK_RETURN))
		game->ChangeState("PlayingState");
    if (input->DidVKeyJustGoDown(VK_ESCAPE))
        game->Exit();
}