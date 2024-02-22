#include <Windows.h>
#include <string>
#include <ShObjIdl.h>
#include <ShlGuid.h>

#define MSG(str) (MessageBoxA(0, str, 0, 0))

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

void CreateShortcut(std::string pSrc, std::string pDst)
{
	HRESULT hres;
	IShellLinkA* psl;

	CoInitialize(NULL);

	hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLinkA, (LPVOID*)&psl);
	if (SUCCEEDED(hres))
	{
		IPersistFile* ppf;

		psl->SetPath(pSrc.data());
		psl->SetIconLocation(pSrc.data(), 0);

		// Save link
		hres = psl->QueryInterface(IID_IPersistFile, (void**)&ppf);
		if (SUCCEEDED(hres))
		{
			hres = ppf->Save(std::wstring(pDst.begin(), pDst.end()).data(), TRUE);
			ppf->Release();
		}

		psl->Release();
	}
}

std::string fileNameFromPath(std::string pPath)
{
	size_t pos = pPath.find_last_of('\\');
	if (pos != std::string::npos)
		return pPath.substr(pos + 1);
	return pPath;
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