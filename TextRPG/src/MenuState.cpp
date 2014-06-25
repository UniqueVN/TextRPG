#include "UIManager.h"
#include "GraphicDevice.h"
#include "Canvas.h"
#include "ConsoleInput.h"
#include "Game.h"
#include "TextGame.h"
#include "UIManager.h"
#include "GameState.h"
#include "MenuState.h"

MenuState::MenuState(void) : GameState("MenuState")
{
}

MenuState::~MenuState(void)
{
}

void MenuState::Update(long period)
{
    UIManager::GetInstance()->Update(period);
    UIManager::GetInstance()->HandleInput();
}

void MenuState::Render()
{
    UIManager::GetInstance()->Render();
}

void MenuState::Begin(State* preState)
{
	GraphicDevice::GetInstance()->SetCursorVisibility(true);

    UIManager::GetInstance()->ShowScreen("MainScreen");
}

void MenuState::End()
{
    UIManager::GetInstance()->CloseTopScreen();
}