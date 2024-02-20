#include "../File.h"
#include <fstream>

int main()
{
	std::ifstream src;
	std::ofstream dst;
	std::string file;

	if (pickFile(file))
	{
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

			// check if autostart already has wallpaper reloader
			src.open("data/.autostart");
			bool exists = false;
			std::string data, binPath = getCurrentDir() + "\\bin\\RlWall.exe";
			while (std::getline(src, data))
			{
				if (binPath == data)
				{
					exists = true;
					break;
				}
			}
			src.close();

			// set wallpaper reloader to autostart if it doesn't already
			if (!exists)
			{
				dst.open("data/.autostart", std::ios::app);
				dst << binPath << '\n';
				dst.close();
			}
		}
	}

	return 0;
}