#pragma once
#include "UIComponent.h"
#include "UILabel.h"

class UIButton : public UILabel
{
public:
    UIButton(UIComponent* parent = NULL);
    virtual ~UIButton(void);

    virtual bool HandleInput();

    void (*OnClick)();
};
