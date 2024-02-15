#include <fstream>
#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
	std::ifstream src;
	std::ofstream dst;

	OPENFILENAME ofn;
	wchar_t szFile[MAX_PATH];

	wchar_t currentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, currentDir);

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = 0;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = L"Images\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn))
	{
		src.open(ofn.lpstrFile, std::ios::binary);
		if (src.is_open())
		{
			SetCurrentDirectory(currentDir);
			CreateDirectory(L"data", 0);
			dst.open("data/wallpaper.jpg", std::ios::binary);
			dst << src.rdbuf();
			dst.close();

			src.seekg(0);
			SetFileAttributesA("C:/cps/wallpaper.jpg", 0);
			dst.open("C:/cps/wallpaper.jpg", std::ios::binary);
			dst << src.rdbuf();
			dst.close();

			src.close();
			SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, NULL, SPIF_UPDATEINIFILE);
		}
	}

	return 0;
}