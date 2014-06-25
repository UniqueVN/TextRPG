#pragma once
#include <vector>
#include <string>
using namespace std;

#include "BasicTypes.h"

#include "lib\pugixml.hpp"
using namespace pugi;

class UIComponent
{
public:
	UIComponent(UIComponent* parent = NULL);
    virtual ~UIComponent(void);

	static UIComponent* Import(const xml_node& xmlNode, UIComponent* parent = NULL);
	// Import support functions
	static bool ImportValueInt(const xml_node& xmlNode, const char* attr, int& value, const int defaultValue = 0);
	static bool ImportValueFloat(const xml_node& xmlNode, const char* attr, float& value, const float defaultValue = 0);
	static bool ImportValueString(const xml_node& xmlNode, const char* attr, string& value);

    virtual void Update(long period);
    virtual void Render();

	virtual bool ImportAttributes(const xml_node& xmlNode);

    string GetID() { return ID; }
    
	string GetText();
	void SetText(const string& text);

	UIComponent* GetChildComponent(const string& id);
	void AddChildComponent(UIComponent* child);

protected:
	virtual void OnInit();
    
	string ID;
	string Text;
	vector2i Pos;       // This is the component's position inside the parent
    vector2i GlobalPos; // This is the global position in the whole screen
    vector2i Size;

	UIComponent* Parent;
	vector<UIComponent*> Children;
    
};