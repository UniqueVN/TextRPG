#pragma once
#include "UIScreen.h"
#include "UIMenu.h"

class MainScreen : public UIScreen
{
public:
    MainScreen(UIComponent* parent = nullptr);
    ~MainScreen(void);

    bool HandleInput();

    void OnPlayClick();
    void OnExitClick();

protected:
     void OnInit();

private:
    UIMenu* MainMenu;
};