#pragma once
#include "UIScreen.h"
#include "UIMenu.h"

class MainScreen : public UIScreen
{
public:
    MainScreen(UIComponent* parent = NULL);
    ~MainScreen(void);

    bool HandleInput();

protected:
     void OnInit();

private:
    UIMenu* MainMenu;  
};