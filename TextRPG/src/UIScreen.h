#pragma once
#include "UIComponent.h"

class UIScreen: public UIComponent
{
public:
    UIScreen(UIComponent* parent = NULL);
    virtual ~UIScreen();

protected:
	virtual void OnInit();
};
