#pragma once
#include "UIComponent.h"

class UIMenu : public UIComponent
{
public:
	UIMenu(UIComponent* parent = NULL);
	virtual ~UIMenu(void);
};
