#include <fstream>
#include <Windows.h>
#include "../../Utils/File.h"

int main()
{
	setCurrentDir(getProgDir() + "\\..\\");

	std::ifstream src;
	std::ofstream dst;

	src.open(L"data/wallpaper.jpg", std::ios::binary);
	if (src.is_open())
	{
		// set cps wallpaper to writable
		SetFileAttributesA("C:/cps/wallpaper.jpg", 0);
		dst.open(L"C:/cps/wallpaper.jpg", std::ios::binary);
		dst << src.rdbuf();
		dst.close();
		src.close();

		SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, (LPWSTR)L"", SPIF_UPDATEINIFILE);
	}

	return 0;
}
