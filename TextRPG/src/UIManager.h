// UIManager - manage the game's UI system: import, update ...

#pragma once
#include <map>
using namespace std;

#include "Singleton.h"
#include "UIComponent.h"
#include "UIScreen.h"

class UIManager : public Singleton<UIManager>
{
public:
    friend class Singleton<UIManager>;

    // Import the UI from an xml file
    bool Import(const char* filePath);

    // Update the UI screens/components
    void Update(long period);
    void Render();
    bool HandleInput(); // Return true if the component handled the input, return false if not

    // Create an UI component from a xml node
    UIComponent* CreateComponent(const xml_node& xmlNode, UIComponent* parent = nullptr);

    void CloseTopScreen();
    bool ShowScreen(const string& screenID);
    void RegisterScreen(UIScreen* newScreen);

protected:
    UIManager(void);
    ~UIManager(void);

    UIComponent* ConstructComponent(const char* type, UIComponent* parent = nullptr);

    UIScreen* CurrentScreen;        // Current screen that are showing on the screen
    map<string, UIScreen*> Screens;
};