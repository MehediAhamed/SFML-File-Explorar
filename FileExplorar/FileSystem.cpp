#include "FileSystem.h"
#include <Windows.h>
#pragma warning(disable:4996)
#pragma comment(lib, "ws2_32.lib")



vector<string> FileSystem::getDirectoriesList(const string & path)
{
	vector<string> filesList;

	unsigned long attribute = GetFileAttributes(path.c_str());
	if (attribute & FILE_ATTRIBUTE_DIRECTORY)
	{
		WIN32_FIND_DATA findFileData;
		void * findFileHandel = FindFirstFile((path + '*').c_str(), &findFileData);
		do
		{
			if ((findFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) == 0 && findFileData.cFileName[0] != '.')
			{

				bool isDirectory = bool(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
				if (isDirectory)
				{
					filesList.push_back(findFileData.cFileName);
				}

			}

		} while (FindNextFile(findFileHandel, &findFileData));
		FindClose(findFileHandel);
	}
	return filesList;
}

vector<string> FileSystem::getDrivesList()
{
	vector<string> filesList;

	char drivesBuf[200];
	unsigned long int bufSize = 200;
	unsigned long int stringsSize = GetLogicalDriveStrings(bufSize, drivesBuf);

	unsigned long int pos = 0;
	char tempBuf[50];
	int tempPos = 0;

	while (pos < stringsSize)
	{
		tempBuf[tempPos] = drivesBuf[pos];
		if (tempBuf[tempPos] == '\0')
		{
			filesList.push_back(tempBuf);
			tempPos = 0;
		}
		else
		{
			++tempPos;
		}
		++pos;
	}

	return filesList;
}
