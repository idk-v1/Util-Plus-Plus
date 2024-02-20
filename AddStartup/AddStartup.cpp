#include "../File.h"
#include "../Process.h"
#include <fstream>

int main()
{
	std::string str;
	std::ofstream listOut;
	std::ifstream listIn;

	if (pickFile(str))
	{
		mkDir("data");

		// checks autostart for duplicate
		bool exists = false;
		std::string data;
		listIn.open("data/.autostart");
		if (listIn.is_open())
		{
			while (std::getline(listIn, data))
			{
				if (str == data)
				{
					exists = true;
					break;
				}
			}
			listIn.close();
		}

		// new entry if it doesn't already exist
		if (!exists)
		{
			listOut.open("data/.autostart", std::ios::app);
			listOut << str << '\n';
			listOut.close();

			// reload program list
			killParentProc();
			startProc("bin/Startup.exe");
		}
	}

	return 0;
}