#include "../../Utils/Process.h"
#include "../../Utils/File.h"
#include "../../Utils/AutoStart.h"

int main(int argc, char* argv[])
{
	setCurrentDir(getProgDir() + "\\..\\");

	bool state = autoStartExists(getCurrentDir() + "\\bin\\UtilLauncherHK.exe");
	if (argc == 2)
	{
		if (state)
		{
			killProc("UtilLauncherHK.exe");
			autoStartRemove(getCurrentDir() + "\\bin\\UtilLauncherHK.exe");
		}
		else
		{
			startProc("bin/UtilLauncherHK.exe");
			autoStartAdd(getCurrentDir() + "\\bin\\UtilLauncherHK.exe");
		}
	}
	return state;
}