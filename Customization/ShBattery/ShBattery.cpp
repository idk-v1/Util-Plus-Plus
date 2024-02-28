#include "../../Utils/Process.h"
#include "../../Utils/File.h"
#include <fstream>

int main(int argc, char* argv[])
{
    if (argc == 2)
    {
		setCurrentDir(getProgDir() + "\\..\\");

		// check if autostart already has battery
		std::ifstream startIn("data/.autostart");
		bool exists = false;
		std::string data, binPath = getCurrentDir() + "\\bin\\BatteryPlusPlus.exe";

		if (startIn.is_open())
		{
			while (std::getline(startIn, data))
			{
				if (binPath == data)
				{
					exists = true;
					break;
				}
			}
			startIn.close();
		}

        if (argv[1][0] - '0')
        {
            startProc("bin/BatteryPlusPlus.exe");

			if (!exists)
			{
				mkDir("data");
				std::ofstream startOut("data/.autostart", std::ios::app);
				startOut << binPath << '\n';
				startOut.close();
			}
        }
        else
        {
			killProc("BatteryPlusPlus.exe");

			if (exists)
			{
				std::string data;
				std::ofstream temp("data/temp");
				startIn.open("data/.autostart");

				while (std::getline(startIn, data))
					if (data != binPath)
						temp << data << '\n';

				startIn.close();
				temp.close();

				remove("data/.autostart");
				rename("data/temp", "data/.autostart");
			}
        }
    }

    return 0;
}