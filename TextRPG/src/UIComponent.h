#pragma once
#include <vector>
#include <string>
using namespace std;

#include "lib\pugixml.hpp"
using namespace pugi;

#include "BasicTypes.h"
#include "EventDispatcher.h"

class UIComponent : public EventDispatcher
{
public:
    UIComponent(UIComponent* parent = nullptr);
    virtual ~UIComponent(void);

    static UIComponent* Import(const xml_node& xmlNode, UIComponent* parent = nullptr);
    // Import support functions
    static bool ImportValueInt(const xml_node& xmlNode, const char* attr, int& value, const int defaultValue = 0);
    static bool ImportValueFloat(const xml_node& xmlNode, const char* attr, float& value, const float defaultValue = 0);
    static bool ImportValueString(const xml_node& xmlNode, const char* attr, string& value);

    virtual void Update(long period);
    virtual void Render();
    virtual bool HandleInput(); // Return true if the component handled the input, return false if not

    virtual bool ImportAttributes(const xml_node& xmlNode);

    string GetID() { return ID; }
    
    string GetText();
    void SetText(const string& text);

    bool IsFocused();
    void SetFocus(const bool newFocus);

    UIComponent* GetChildComponent(const string& id);
    void AddChildComponent(UIComponent* child);

protected:
    virtual void OnInit();
    
    string ID;
    string Text;
    vector2i Pos;       // This is the component's position inside the parent
    vector2i GlobalPos; // This is the global position in the whole screen
    vector2i Size;

    bool bFocused;
    //bool bDisabled;
    //bool bVisible;

    UIComponent* Parent;
    vector<UIComponent*> Children;    
};