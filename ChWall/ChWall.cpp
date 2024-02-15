#include <fstream>
#include <Windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	std::ifstream src;
	std::ofstream dst;

	OPENFILENAME ofn;
	wchar_t szFile[260];

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
			_wmkdir(L"C:/wallpaper");
			dst.open(L"C:/wallpaper/wallpaper.jpg", std::ios::binary);
			dst << src.rdbuf();
			dst.close();

			src.seekg(0);
			SetFileAttributes(L"C:/cps/wallpaper.jpg", 0);
			dst.open(L"C:/cps/wallpaper.jpg", std::ios::binary);
			dst << src.rdbuf();
			dst.close();

			src.close();
			SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, (LPWSTR)L"", SPIF_UPDATEINIFILE);
		}
	}

	return 0;
}