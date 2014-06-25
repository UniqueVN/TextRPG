#include "ConsoleInput.h"
#include "UIComponent.h"
#include "UILabel.h"
#include "UIButton.h"

UIButton::UIButton(UIComponent* parent) : UILabel(parent)
{
}

UIButton::~UIButton(void)
{
}

bool UIButton::HandleInput()
{
    bool bHandle = UIComponent::HandleInput();
    if (bHandle)
        return true;

	ConsoleInput* input = ConsoleInput::GetInstance();
	if (input->DidVKeyJustGoDown(VK_RETURN))
	{
        bHandle = true;
        OnClick();
	}

    return bHandle;
}
