#include <fstream>
#include <string>
#include <Windows.h>
#include "../../Utils/File.h"


int main()
{
	setCurrentDir(getProgDir() + "\\..\\");

	std::ifstream list("data/.autostart");
	std::string data;

	if (list.is_open())
	{
		while (std::getline(list, data))
			ShellExecuteA(0, 0, data.data(), 0, 0, SW_SHOW);

		list.close();

	}

	return 0;
}