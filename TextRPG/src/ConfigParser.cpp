#include <string>
using namespace std;
#include <cstdio>
#include <cctype>

#include "FileUtil.h"

#include "ConfigData.h"
#include "ConfigParser.h"

ConfigParser::ConfigParser()
{
}

ConfigParser::~ConfigParser()
{
}

ConfigDataSet* ConfigParser::ParseFile(const char* fileName)
{
    _content = FileUtil::GetContent(fileName);
    _curSection = 0;
    if (_content == 0)
        return 0;

    ConfigDataSet* data = new ConfigDataSet();

    // Parse included files add the head of this file
    // ;; - include other ini file
    string dirPath = fileName;
    int t = dirPath.rfind("/");
    if (t == 0)
        dirPath = "";
    else
        dirPath.erase(t + 1, dirPath.length() - t);
    string filePath = "";
    ConfigParser* includedParser = new ConfigParser();
    while (*_content == ';')
    {
        if (*(_content + 1) == ';')
        {
            _content += 2;
            // Get the name of included file
            filePath = "";
            while (*_content != '\n')
                filePath += *(_content++);
            filePath = dirPath + filePath + ".ini";
            
            ConfigDataSet* newData = includedParser->ParseFile(filePath.c_str());
            data->AddData(newData);
            
            NextLine();
        }
        else 
            break;
    }

    // Parse all content
    while (true)
    {
        switch (*_content)
        {
        case '\0':
            return data;
        // Ignore empty/space character
        case ' ':
        case '\t':
        case '\n':
            _content++;
            break;
        // Ignore comment line
        case ';':
            NextLine();
            break;
        // Parse a new section
        case '[':
        {
            // Get the section's name
            _content++;
            string newSection;
            while (*_content != ']')
            {
                newSection += *_content;
                *_content++;
            }

            // Create new section
            _curSection = data->AddSection(newSection);

            // Change to next line
            NextLine();
            break;
        }
        // Parse a pair of key & value
        default:
        {
            string key;
            // Get the key
            while ((*_content != '=') && (!isspace(*_content)))
            {
                key += *_content;
                _content++;
            }
            
            IgnoreSpace();

            if (*_content == '=')
                _content++;
            // If there's no assigment operator => there're errors in this line
            else
            {
                NextLine();
                break;
            }

            IgnoreSpace();
            // Get the value
            string value;
            //while ((*_content != '\0') && !isspace(*_content))
            while ((*_content != '\0') && (*_content != '\n'))
            {
                value += *_content;
                _content++;
            }
            NextLine();

            _curSection->AddData(key, value);

            // Get the value
            break;
        }
        }
    }

    return data;
}

int ConfigParser::ParseInt(const string& strValue)
{
    int value = 0;
    for (int i = 0; i < (int)strValue.length(); i++)
    {
        if (isdigit(strValue[i]))
            value = value * 10 + (strValue[i] - '0');
        else
            break;
    }

    return value;
}

float ConfigParser::ParseFloat(const string& strValue)
{
    return (float)atof(strValue.c_str());
}

inline void ConfigParser::NextLine()
{
    while ((*_content != '\n') && (*_content != '\0'))
        _content++;

    if (*_content == '\n')
        _content++;
}

inline void ConfigParser::IgnoreSpace()
{
    while (isspace(*_content) && (*_content != '\0'))
        _content++;
}

