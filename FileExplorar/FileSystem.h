#pragma once
#include <string>
#include <vector>
using namespace std;
class FileSystem
{
public:
	
	static vector<string> getDirectoriesList(const string & path);
	static vector<string> getDrivesList();
};