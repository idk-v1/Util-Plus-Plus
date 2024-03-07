#include "../../Utils/File.h"
#include "../../Utils/Autostart.h"
#include <fstream>

int main()
{
	std::ifstream src;
	std::ofstream dst;
	std::string file;

	if (pickFile(file))
	{
		setCurrentDir(getProgDir() + "\\..\\");

		src.open(file, std::ios::binary);
		if (src.is_open())
		{
			// store wallpaper to copy in dat folder
			mkDir("data");
			dst.open("data/wallpaper.jpg", std::ios::binary);
			dst << src.rdbuf();
			dst.close();

			// set cps wallpaper to writable and overwrite it
			src.seekg(0);
			SetFileAttributesA("C:/cps/wallpaper.jpg", 0);
			dst.open("C:/cps/wallpaper.jpg", std::ios::binary);
			dst << src.rdbuf();
			dst.close();
			src.close();

			// reload wallpaper
			SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, NULL, SPIF_UPDATEINIFILE);

			// set wallpaper reloader to autostart if it doesn't already
			if (!autoStartExists(getCurrentDir() + "\\bin\\RlWall.exe"))
				autoStartAdd(getCurrentDir() + "\\bin\\RlWall.exe");
		}
	}

	return 0;
}