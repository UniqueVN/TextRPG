#pragma once
#include "UIComponent.h"

class UILabel : public UIComponent
{
public:
    UILabel(UIComponent* parent = nullptr);
    virtual ~UILabel(void);

    virtual void Render();
};
