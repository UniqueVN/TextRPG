#include "Canvas.h"

#include "UIComponent.h"
#include "UILabel.h"

UILabel::UILabel(UIComponent* parent) : UIComponent(parent)
{
}

UILabel::~UILabel(void)
{
}

void UILabel::Render()
{
    // Render the text at the right location
    Canvas* canvas = Canvas::GetInstance();
    canvas->ShowText(Text.c_str(), GlobalPos, FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_WHITE);

    UIComponent::Render();
}
