#include "GraphicDevice.h"
#include "ConsoleInput.h"
#include "Game.h"
#include "TextGame.h"

#include "Canvas.h"
#include "UIButton.h"
#include "UIMenu.h"
#include "UIScreen.h"
#include "MainScreen.h"

void OnPlayClick();
void OnExitClick();

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
    
    // TODO: Set up the event the system, bind the event OnClick to member function of the screen instead of global function like this
    UIButton* btnPlay = dynamic_cast<UIButton*>(MainMenu->GetChildComponent("btnPlay"));
    btnPlay->OnClick = OnPlayClick;

    UIButton* btnExit = dynamic_cast<UIButton*>(MainMenu->GetChildComponent("btnExit"));
    btnExit->OnClick = OnExitClick;
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

void OnPlayClick()
{
    TextGame::GetInstance()->ChangeState("PlayingState");
}

void OnExitClick()
{
    TextGame::GetInstance()->Exit();
}
