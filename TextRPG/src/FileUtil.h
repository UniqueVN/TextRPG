#pragma once

class FileUtil
{
public:
    FileUtil(void);
    ~FileUtil(void);

    static char* GetContent(const char* fileName);
};
