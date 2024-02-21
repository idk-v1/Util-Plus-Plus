#include <Windows.h>
#include <string>

bool pickFile(std::string& pPath)
{
	OPENFILENAMEA ofn;
	char fileName[MAX_PATH], currentDir[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, currentDir);

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = fileName;
	ofn.lpstrFile[0] = 0;
	ofn.nMaxFile = sizeof(fileName);
	ofn.lpstrFilter = "";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;


	if (GetOpenFileNameA(&ofn))
	{
		pPath = ofn.lpstrFile;
		SetCurrentDirectoryA(currentDir);
		return true;
	}

	SetCurrentDirectoryA(currentDir);
	return false;
}

bool mkDir(std::string pName)
{
	return CreateDirectoryA(pName.data(), 0);
}

std::string getCurrentDir()
{
	char path[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, path);
	return std::string(path);
}

void setCurrentDir(std::string pPath)
{
	SetCurrentDirectoryA(pPath.data());
}

std::string getProgDir()
{
	char path[MAX_PATH];
	GetModuleFileNameA(NULL, path, MAX_PATH);
	std::string str(path);
	str.erase(str.find_last_of('\\'), std::string::npos);
	return str;
}