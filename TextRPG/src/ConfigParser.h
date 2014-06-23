#pragma once
#include <string>
#include "ConfigData.h"

class ConfigParser
{
public:
    ConfigParser();
    ~ConfigParser();

    ConfigDataSet* ParseFile(const char* fileName);

    static int ParseInt(const string&);
    static float ParseFloat(const string&);

protected:
    inline void NextLine();
    inline void IgnoreSpace();

    char* _content;
    ConfigData* _curSection;  // Parsing section
};