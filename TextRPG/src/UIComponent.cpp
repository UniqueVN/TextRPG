#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

#include "BasicTypes.h"
#include "UIManager.h"
#include "UIComponent.h"

#include "lib\pugixml.hpp"
using namespace pugi;

UIComponent::UIComponent(UIComponent* parent) : Parent(parent),
        Pos(-1, -1),
        Size(-1, -1),
		Text(""),
		ID(""),
        bFocused(false)
{
}

UIComponent::~UIComponent(void)
{
    // Delete all the child components
    for (vector<UIComponent*>::iterator it = Children.begin(); it != Children.end(); it++)
    {
        if (*it)
            delete (*it);
    }

    Children.clear();
}

// Update window's events
void UIComponent::Update(long period)
{
    bool bSizeDirtied = Size == vector2i(-1, -1);
    // Calculate the component's size base on its text if it's not specified
    // TODO: check how many lines does the text have and find which is maximum width of a line
    // For now just assume it's 1 line text
    if (bSizeDirtied)
    {
        Size.X = Text.length();
        Size.Y = 1;
    }

    // TODO: Only need to calculate the position if the component or its parent moved
    // Calculate the component's global position from its parent
    GlobalPos = (Parent ? Parent->GlobalPos : vector2i(0, 0)) + Pos;

    // Update all the child components
    vector2i childPos;
    for (vector<UIComponent*>::iterator it = Children.begin(); it != Children.end(); it++)
    {
        UIComponent* childItem = *it;

        // If the child item doesn't have position specified then calculate it
        if (childItem->Pos == vector2i(-1, -1))
        {
            childItem->Pos = childPos;
        }
        else
        {
            childPos = childItem->Pos;
        }

        childItem->Update(period);

        // Auto-expand the component size if its items cover more area out of it
        if (bSizeDirtied)
        {
            if (childItem->Size.X > Size.X)
                Size.X = childItem->Size.X;

            Size.Y += childItem->Size.Y;
        }

        // TODO: Need to handle different type of auto-position. Only make item appear vertical for now
        childPos.Y += childItem->Size.Y;
    }
}

void UIComponent::Render()
{
    // Render all the child components
    for (vector<UIComponent*>::iterator it = Children.begin(); it != Children.end(); it++)
    {
        (*it)->Render();
    }
}

bool UIComponent::HandleInput()
{
    // Need to implement this function in the child class
    return false;
}

UIComponent* UIComponent::Import(const xml_node& xmlNode, UIComponent* parent)
{
	// Create the component from the node's attributes
	UIComponent* newComponent = UIManager::GetInstance()->CreateComponent(xmlNode, parent);

	// Process the child nodes
	for (xml_node_iterator it = xmlNode.begin(); it != xmlNode.end(); ++it)
	{
		UIComponent* child = Import(*it, newComponent);
		newComponent->AddChildComponent(child);
	}

	newComponent->OnInit();
	
	return newComponent;
}

bool UIComponent::ImportValueInt(const xml_node& xmlNode, const char* attr, int& value, const int defaultValue)
{
    const char* attrValue = xmlNode.attribute(attr).value();
    if (strcmp(attrValue, "") == 0)
    {
        value = defaultValue;
        return false;
    }

    value = atoi(attrValue);
	return true;
}

bool UIComponent::ImportValueFloat(const xml_node& xmlNode, const char* attr, float& value, const float defaultValue)
{
    const char* attrValue = xmlNode.attribute(attr).value();
    if (strcmp(attrValue, "") == 0)
    {
        value = defaultValue;
        return false;
    }

	value = (float)atof(attrValue);
	return true;
}

bool UIComponent::ImportValueString(const xml_node& xmlNode, const char* attr, string& value)
{
	const char* attrValue = xmlNode.attribute(attr).value();

    value = string(attrValue);
	return true;
}

bool UIComponent::ImportAttributes(const xml_node& xmlNode)
{
	// Parse the needed attributes from the xml node
	ImportValueString(xmlNode, "id", ID);
	ImportValueString(xmlNode, "text", Text);
	ImportValueInt(xmlNode, "x", Pos.X, -1);
	ImportValueInt(xmlNode, "y", Pos.Y, -1);
	ImportValueInt(xmlNode, "width", Size.X, -1);
	ImportValueInt(xmlNode, "height", Size.Y, -1);

	return true;
}

string UIComponent::GetText()
{
	return Text;
}

void UIComponent::SetText(const string& newText)
{
    Text = newText;
}

bool UIComponent::IsFocused()
{
    return bFocused;
}

void UIComponent::SetFocus(const bool newFocus)
{
    if (newFocus == bFocused)
        return;

    bFocused = newFocus;
}

UIComponent* UIComponent::GetChildComponent(const string& id)
{
    for (vector<UIComponent*>::iterator it = Children.begin(); it != Children.end(); it++)
    {
        if (*it && (*it)->ID == id)
            return *it;
    }

	return NULL;
}

void UIComponent::AddChildComponent(UIComponent* child)
{
    if (!child)
		return;

    Children.push_back(child);
}

void UIComponent::OnInit()
{
    // TODO
}