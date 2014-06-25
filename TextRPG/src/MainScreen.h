#pragma once
#include "UIScreen.h"

class MainScreen : public UIScreen
{
public:
    MainScreen(UIComponent* parent = NULL);
    ~MainScreen(void);

    void Update(long period);
};
