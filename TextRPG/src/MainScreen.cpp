#include <functional>

#include "GraphicDevice.h"
#include "ConsoleInput.h"
#include "Game.h"
#include "TextGame.h"

#include "Canvas.h"
#include "UIButton.h"
#include "UIMenu.h"
#include "UIScreen.h"
#include "MainScreen.h"

MainScreen::MainScreen(UIComponent* parent) : UIScreen(parent)
{
}

MainScreen::~MainScreen(void)
{
}

void MainScreen::OnInit()
{
    UIScreen::OnInit();

    MainMenu = dynamic_cast<UIMenu*>(GetChildComponent("mnMain"));
    
    UIButton* btnPlay = dynamic_cast<UIButton*>(MainMenu->GetChildComponent("btnPlay"));
    btnPlay->AddEventListener("OnClick", std::bind(&MainScreen::OnPlayClick, this));

    UIButton* btnExit = dynamic_cast<UIButton*>(MainMenu->GetChildComponent("btnExit"));
    btnExit->AddEventListener("OnClick", std::bind(&MainScreen::OnExitClick, this));
    //btnExit->RemoveEventListener("OnClick", std::bind(&MainScreen::OnExitClick, this));
}

bool MainScreen::HandleInput()
{
    bool bHandled = UIComponent::HandleInput();
    if (bHandled)
        return true;

    TextGame* game = TextGame::GetInstance();

	ConsoleInput* input = ConsoleInput::GetInstance();

    // Let the main menu handle input first
    if (MainMenu && MainMenu->HandleInput())
    {
        return true;
    }

    if (input->DidVKeyJustGoDown(VK_ESCAPE))
    {
        game->Exit();
        return true;
    }

    return false;
}

void MainScreen::OnPlayClick()
{
    TextGame::GetInstance()->ChangeState("PlayingState");
}

void MainScreen::OnExitClick()
{
    TextGame::GetInstance()->Exit();
}
