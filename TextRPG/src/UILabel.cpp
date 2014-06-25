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
    //Color textColor = FOREGROUND_BLUE;
    Color textColor = FOREGROUND_WHITE;
    Color bgColor = BACKGROUND_BLACK;

    if (bFocused)
    {
        textColor = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        //bgColor |= BACKGROUND_INTENSITY;
    }

    canvas->ShowText(Text.c_str(), GlobalPos, textColor | bgColor);

    UIComponent::Render();
}
