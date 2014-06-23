#pragma once
#include <string>
#include <vector>
#include <map>
using namespace std;
#include "vector2.h"

class ConfigDataSet;
class ConfigParser;

class ConfigData
{
public:    
    friend class ConfigDataSet;
    ConfigData(const string& name);
    ~ConfigData();
    
    string GetName() const;

    ConfigDataSet* GetConfigData() const;
    
    // Get the value and convert it to the desired type
    string GetValue(const string& key) const;
    char* GetStringValue(const string& key) const;
    int GetIntValue(const string& key) const;
    float GetFloatValue(const string& key) const;
    bool GetBoolValue(const string& key) const;
    int GetColorValue(const string& key) const;
    vector2f GetVector2fValue(const string& key) const;
    vector<string> GetListValue(const string& key) const;
    vector<vector2f> GetListVector2fValue(const string& key) const;

    bool HasKey(const string& key) const;

    map<string, string> GetData();

    void AddData(const string& key, const string& value);

protected:
    string _name;
    map<string, string> _data;  // Map between key & value in this section
    ConfigDataSet* _configData;    // The whole config data that contain this section
};

class ConfigDataSet
{
public:
    friend class ConfigParser;

    ConfigDataSet(void);
    ~ConfigDataSet(void);

    ConfigData* GetSection(const string& name) const;

    string GetValue(const string& section, const string& key) const;
    int GetIntValue(const string& section, const string& key) const;
    float GetFloatValue(const string& section, const string& key) const;

    ConfigData* AddSection(const string& name);

    // Merge other config data into this
    void AddData(ConfigDataSet*);

protected:
    map<string, ConfigData*> _sections;
};