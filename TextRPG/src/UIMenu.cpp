#include "ConsoleInput.h"
#include "UIComponent.h"
#include "UIMenu.h"

UIMenu::UIMenu(UIComponent* parent) : UIComponent(parent),
            SelectedIndex(-1)
{
}

UIMenu::~UIMenu(void)
{
}

void UIMenu::OnInit()
{
    UIComponent::OnInit();

    // By default select the first item in the list
    SelectItemAtIndex(0);
}

UIComponent* UIMenu::GetSelectedItem()
{
    if (SelectedIndex < 0 || SelectedIndex >= (int)Children.size())
        return 0;

    return Children[SelectedIndex];
}

bool UIMenu::SelectItemAtIndex(const int newIndex)
{
    if (newIndex < 0 || newIndex >= (int)Children.size() || newIndex == SelectedIndex)
        return false;

    // Unfocus the currently selected item
    UIComponent* curSelectedItem = GetSelectedItem();
    if (curSelectedItem)
        curSelectedItem->SetFocus(false);

    SelectedIndex = newIndex;

    // Focus on the new selected item
    curSelectedItem = GetSelectedItem();
    if (curSelectedItem)
        curSelectedItem->SetFocus(true);

    return true;
}

bool UIMenu::HandleInput()
{
    bool bHandle = UIComponent::HandleInput();
    if (bHandle)
        return true;

    int itemCount = Children.size();
    int newIndex = SelectedIndex;

	ConsoleInput* input = ConsoleInput::GetInstance();
	if (input->DidVKeyJustGoDown(VK_UP))
	{
        bHandle = true;

        newIndex--;
		if (newIndex < 0)
			newIndex = itemCount - 1;
	}
	else if (input->DidVKeyJustGoDown(VK_DOWN))
	{
        bHandle = true;

		newIndex++;
		if (newIndex > itemCount - 1)
			newIndex = 0;
	}

    // Let the current selected item handle other input keys
    if (!bHandle)
    {
        UIComponent* curSelectedItem = GetSelectedItem();
        if (curSelectedItem)
            bHandle = curSelectedItem->HandleInput();
    }
    else
    {
        SelectItemAtIndex(newIndex);
    }

    return bHandle;
}