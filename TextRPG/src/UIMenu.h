#pragma once
#include "UIComponent.h"

class UIMenu : public UIComponent
{
public:
    UIMenu(UIComponent* parent = NULL);
    virtual ~UIMenu(void);

    bool HandleInput();

    UIComponent* GetSelectedItem();
    bool SelectItemAtIndex(const int index);

protected:
    void OnInit();

private:
    int SelectedIndex; // Index of the selected child item
};
