// Thank you Ciantic!
// https://stackoverflow.com/a/25812667

#include <Windows.h>
#include <fstream>
#include "../File.h"

int main()
{
	ShellExecuteA(NULL, "taskbarunpin", "C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\Outlook.lnk", NULL, NULL, 0);
	ShellExecuteA(NULL, "taskbarunpin", "C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\Google Chrome.lnk", NULL, NULL, 0);

	setCurrentDir(getProgDir() + "\\..\\");
	mkDir("data");
	
	std::ifstream src;
	std::ofstream dst;

	// check if autostart already has wallpaper reloader
	src.open("data/.autostart");
	bool exists = false;
	std::string data, binPath = getCurrentDir() + "\\bin\\RmDefTaskbarPins.exe";
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

	return 0;
}