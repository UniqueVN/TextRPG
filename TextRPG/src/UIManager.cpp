#include <sstream>
#include <map>
using namespace std;

#include "UIComponent.h"
#include "UIButton.h"
#include "UILabel.h"
#include "UIMenu.h"

#include "UIScreen.h"
#include "MainScreen.h"

#include "lib\pugixml.hpp"
using namespace pugi;

#include "UIManager.h"

UIManager::UIManager(void) : CurrentScreen(nullptr)
{
	
}

UIManager::~UIManager(void)
{
	for (auto screenIt : Screens)
    {
        if (screenIt.second)
        {
            delete screenIt.second;
            screenIt.second = nullptr;
        }
    }

    Screens.clear();
}

// Import the UI from an xml file
bool UIManager::Import(const char* filePath)
{
	xml_document doc;
	xml_parse_result result = doc.load_file(filePath);

	// Notify there're error in the xml file
	if (!result)
	{
		std::stringstream errorStr;
		errorStr << "XML file [" << filePath << "] parsed with errors:\n"
			<< "Error description: " << result.description() << "\n"
			<< "Error offset: " << result.offset;

        // TODO: print out the error on the screen
		return false;
	}

	// Process the child nodes in the documennt, ignore the root
	for (xml_node_iterator it = doc.begin(); it != doc.end(); ++it)
	{
		UIComponent::Import(*it);
	}

	return true;
}

void UIManager::Update(long period)
{
    if (CurrentScreen)
        CurrentScreen->Update(period);
}

void UIManager::Render()
{
    if (CurrentScreen)
        CurrentScreen->Render();
}

bool UIManager::HandleInput()
{
    if (CurrentScreen)
        return CurrentScreen->HandleInput();

    return false;
}

UIComponent* UIManager::ConstructComponent(const char* type, UIComponent* parent)
{
#define CHECK_COMPONENT(value, className) \
	if (strcmp(type, value) == 0) return new className(parent);

	CHECK_COMPONENT("Button", UIButton);
	CHECK_COMPONENT("Label", UILabel);
	CHECK_COMPONENT("Menu", UIMenu);

    CHECK_COMPONENT("Screen", UIScreen);
    CHECK_COMPONENT("MainScreen", MainScreen);

    // If can't find the component class then just create a default UI component from it
	return new UIComponent(parent);
}

UIComponent* UIManager::CreateComponent(const xml_node& xmlNode, UIComponent* parent)
{
	UIComponent* newComponent = ConstructComponent(xmlNode.name(), parent);
	newComponent->ImportAttributes(xmlNode);

	return newComponent;
}

void UIManager::CloseTopScreen()
{
    if (CurrentScreen)
    {
        CurrentScreen = 0;
    }
}

bool UIManager::ShowScreen(const string& screenID)
{
	map<string, UIScreen*>::iterator screenIt = Screens.find(screenID);
	if (screenIt == Screens.end())
		return false;

    CurrentScreen =  dynamic_cast<UIScreen*>(screenIt->second);

    return true;
}

void UIManager::RegisterScreen(UIScreen* newScreen)
{
    if (!newScreen || newScreen->GetID().empty())
		return;

    Screens.insert(std::pair<string, UIScreen*>(newScreen->GetID(), newScreen));
}