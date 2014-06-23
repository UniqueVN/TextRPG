#include <sys/stat.h>
#include <cstdio>

#include "FileUtil.h"

FileUtil::FileUtil(void)
{
}

FileUtil::~FileUtil(void)
{
}

char* FileUtil::GetContent(const char* fileName)
{
   // Load content of the file
    FILE *file;
	fopen_s(&file, fileName, "r");
    struct _stat fileStats;

    // If cannot find the file => return an empty string
    if ((file == 0) || (_stat(fileName, &fileStats) != 0))
	{
        return 0;
	}

    char* content = new char[fileStats.st_size];

	// Read whole content of the file
	int bytes = fread(content, 1, fileStats.st_size, file);
	content[bytes] = 0;

    fclose( file );

    return content;
}
