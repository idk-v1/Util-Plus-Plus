#include <fstream>
#include <Windows.h>

int main()
{
	std::ifstream src;
	std::ofstream dst;

	src.open(L"C:/wallpaper/wallpaper.jpg", std::ios::binary);
	if (src.is_open())
	{
		SetFileAttributes(L"C:/cps/wallpaper.jpg", 0);
		dst.open(L"C:/cps/wallpaper.jpg", std::ios::binary);
		dst << src.rdbuf();
		dst.close();
		src.close();

		SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, (LPWSTR)L"", SPIF_UPDATEINIFILE);
	}

	return 0;
}
