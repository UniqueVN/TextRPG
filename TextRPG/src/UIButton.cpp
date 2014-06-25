#include "UIComponent.h"
#include "UILabel.h"
#include "UIButton.h"

UIButton::UIButton(UIComponent* parent) : UILabel(parent)
{
}

UIButton::~UIButton(void)
{
}
