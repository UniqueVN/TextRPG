#pragma once
#include <functional>
#include "UIComponent.h"
#include "UILabel.h"

class UIButton : public UILabel
{
public:
    UIButton(UIComponent* parent = nullptr);
    virtual ~UIButton(void);

    virtual bool HandleInput();
};
