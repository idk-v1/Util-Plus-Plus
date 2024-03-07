#include "../../Utils/Process.h"
#include "../../Utils/File.h"
#include "../../Utils/AutoStart.h"

int main(int argc, char* argv[])
{
	setCurrentDir(getProgDir() + "\\..\\");

	bool state = autoStartExists(getCurrentDir() + "\\bin\\BatteryPlusPlus.exe");
	if (argc == 2)
	{
		if (state)
		{
			killProc("BatteryPlusPlus.exe");
			autoStartRemove(getCurrentDir() + "\\bin\\BatteryPlusPlus.exe");
		}
		else
		{
			startProc("bin/BatteryPlusPlus.exe");
			autoStartAdd(getCurrentDir() + "\\bin\\BatteryPlusPlus.exe");
		}
	}
	return state;
}