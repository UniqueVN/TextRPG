#include "UIComponent.h"
#include "UIManager.h"
#include "UIScreen.h"

UIScreen::UIScreen(UIComponent* parent) : UIComponent(parent)
{
    // Register this screen with the UIManager
}

UIScreen::~UIScreen(void)
{
}

void UIScreen::OnInit()
{
    UIComponent::OnInit();

    UIManager* manager = UIManager::GetInstance();
    manager->RegisterScreen(this);

    // Auto make the screen align to the top-left of the screen if its position not specified
    if (Pos == vector2i(-1, -1))
        Pos = vector2i(0, 0);
}