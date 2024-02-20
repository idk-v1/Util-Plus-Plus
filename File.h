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
	char currentDir[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, currentDir);
	return std::string(currentDir);
}