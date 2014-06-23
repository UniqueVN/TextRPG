#include <string>
#include <map>
#include "ConfigData.h"
using namespace std;
#include "vector2.h"

/// CONFIGURATION SECTION
ConfigData::ConfigData(const string& name) : _name(name)
{
}

ConfigData::~ConfigData()
{
    _data.clear();
}

string ConfigData::GetName() const
{
    return _name;
}

ConfigDataSet* ConfigData::GetConfigData() const
{
    return _configData;
}

string ConfigData::GetValue(const string& key) const
{
    map<string, string>::const_iterator iter = _data.find(key);
    if (iter != _data.end())
        return iter->second;

    return "";
}

char* ConfigData::GetStringValue(const string& key) const
{
    map<string, string>::const_iterator iter = _data.find(key);
    if (iter != _data.end())
    {
        int len = iter->second.length() + 1;
        char* value = new char[len];
        strcpy_s(value, len, iter->second.c_str());
        return value;
    }

    return 0;
}

int ConfigData::GetIntValue(const string& key) const
{
    map<string, string>::const_iterator iter = _data.find(key);
    if (iter != _data.end())
        return atoi(iter->second.c_str());

    return 0;
}

float ConfigData::GetFloatValue(const string& key) const
{
    map<string, string>::const_iterator iter = _data.find(key);
    if (iter != _data.end())
        return (float)atof(iter->second.c_str());

    return 0.f;
}

bool ConfigData::GetBoolValue(const string& key) const
{
    map<string, string>::const_iterator iter = _data.find(key);
    if (iter != _data.end())
    {
        if ((iter->second == "true") || (iter->second == "1"))
            return true;
        else
            return false;
    }

    return false;
}

int ConfigData::GetColorValue(const string& key) const
{
    map<string, string>::const_iterator iter = _data.find(key);
    if (iter != _data.end())
    {
        string str = iter->second;
        int t = 0;
        while (isspace(str[t]))
            t++;

        int value = 0;
        int digit;
        while (!isspace(str[t]))
        {
            char ch = tolower(str[t]);

            if (('0' <= ch) && (ch <= '9'))
                digit = ch - '0';
            else  if (('a' <= ch) && (ch <= 'f'))
                digit = ch - 'a' + 10;
            else
                break;

            value = (value << 4) + digit;
            t++;
        }
        return value;
    }

    return 0;
}

// (X, Y)
vector2f ConfigData::GetVector2fValue(const string& key) const
{
    map<string, string>::const_iterator iter = _data.find(key);
    if (iter != _data.end())
    {
        string str = iter->second;
        int t = str.find('(') + 1;
        string xStr = "";
        while ((str[t] != ' ') && (str[t] != ','))
            xStr += str[t++];
        while (!isdigit(str[t]))
            t++;
        string yStr = "";
        while ((str[t] != ' ') && (str[t] != ')'))
            yStr += str[t++];

        return vector2f((float)atof(xStr.c_str()), (float)atof(yStr.c_str()));
    }

    return vector2f();
}

vector<string> ConfigData::GetListValue(const string& key) const
{
    map<string, string>::const_iterator iter = _data.find(key);
    if (iter != _data.end())
    {
        vector<string> valueList;
        string str = iter->second;
        int t = str.find('(') + 1;
        string value = "";
		while ((t < (int)str.length()) && (str[t] != '"'))
            t++;
		if ((t >= (int)str.length()) || (str[t] == ')'))
			return valueList;
        t++;
        while (str[t] != ')')
        {
            while (str[t] != '"')
            {
                if (str[t] == '\\')
                {
                    t++;
                    if (str[t++] == 'n')
                    {
                        value += '\n';
                    }
                    else if (str[t++] == 't')
                        value += '\t';
                    else 
                    {
                        value += '\\';
                        value += str[t - 1];
                    }
                }
                else
                    value += str[t++];
            }
            t++;
            while ((t < (int)str.length()) && (str[t] != ',') && (str[t] != ')'))
                t++;
            if (t >= (int)str.length())
                break;
            if (str[t] == ',')
            {
                valueList.push_back(value);
                value = "";
                while (str[t] != '"')
                    t++;
                t++;
            }
            else if (str[t] == ')')
            {
                valueList.push_back(value);
                break;
            }
        }

        return valueList;
    }
    return vector<string>();
}

vector<vector2f> ConfigData::GetListVector2fValue(const string& key) const
{
    map<string, string>::const_iterator iter = _data.find(key);
    if (iter != _data.end())
    {
        vector<vector2f> valueList;
        string str = iter->second;
        int t = str.find('(') + 1;
        string value = "";
		vector2f v;
		while (t < (int)str.length())
        {
			while ((str[t] == ' ') || (str[t] == ','))
				t++;
			if (str[t] != '(')
				break;

			t++;
			value = "";
			while (isdigit(str[t]))
			{
				value += str[t];
				t++;
			}
			v.X = (float)atof(value.c_str());
			
			while ((str[t] == ' ') || (str[t] == ','))
				t++;
			value = "";
			while (isdigit(str[t]))
			{
				value += str[t];
				t++;
			}
			v.Y = (float)atof(value.c_str());

			while (str[t] != ')')
				t++;
			t++;
			valueList.push_back(v);
        }

        return valueList;
    }
    return vector<vector2f>();
}

bool ConfigData::HasKey(const string& key) const
{
    map<string, string>::const_iterator iter = _data.find(key);
    if (iter != _data.end())
        return true;
    return false;
}

map<string, string> ConfigData::GetData()
{
    return _data;
}

void ConfigData::AddData(const string& key, const string& value)
{
    _data.insert(pair<string, string>(key, value));
}

/// CONFIGURATION DATA
ConfigDataSet::ConfigDataSet(void)
{
}

ConfigDataSet::~ConfigDataSet(void)
{
}

ConfigData* ConfigDataSet::GetSection(const string& name) const
{
    map<string, ConfigData*>::const_iterator iter = _sections.find(name);   
    if (iter != _sections.end())
        return iter->second;
    return 0;
}

string ConfigDataSet::GetValue(const string& section, const string& key) const
{ 
    map<string, ConfigData*>::const_iterator iter = _sections.find(section);
    if (iter != _sections.end())
        return iter->second->GetValue(key);
    return "";
}

int ConfigDataSet::GetIntValue(const string& section, const string& key) const
{
    map<string, ConfigData*>::const_iterator iter = _sections.find(section);
    if (iter != _sections.end())
        return atoi(iter->second->GetValue(key).c_str());
    return 0;
}

float ConfigDataSet::GetFloatValue(const string& section, const string& key) const
{
    map<string, ConfigData*>::const_iterator iter = _sections.find(section);
    if (iter != _sections.end())
        return (float)atof(iter->second->GetValue(key).c_str());
    return 0.f;
}

ConfigData* ConfigDataSet::AddSection(const string& name)
{
    ConfigData* newSection = new ConfigData(name);
    newSection->_configData = this;
    _sections.insert(pair<string, ConfigData*>(name, newSection));
    return newSection;
}

// Merge this configuration with other
void ConfigDataSet::AddData(ConfigDataSet* other)
{
    if (other == 0)
        return;

    for (map<string, ConfigData*>::iterator iter = other->_sections.begin(); 
        iter != other->_sections.end(); iter++)
    {
        string sectName = iter->first;
        ConfigData* newSection = iter->second;
        newSection->_configData = this;
        _sections.insert(pair<string, ConfigData*>(sectName, newSection));
    }
}
