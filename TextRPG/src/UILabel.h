#pragma once
#include "UIComponent.h"

class UILabel : public UIComponent
{
public:
    UILabel(UIComponent* parent = NULL);
    virtual ~UILabel(void);

    virtual void Render();
};
