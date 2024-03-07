#include "../../Utils/Process.h"
#include "../../Utils/File.h"
#include "../../Utils/AutoStart.h"

int main(int argc, char* argv[])
{
	setCurrentDir(getProgDir() + "\\..\\");

	bool state = autoStartExists(getCurrentDir() + "\\bin\\PwshLauncherHK.exe");
	if (argc == 2)
	{
		if (state)
		{
			killProc("PwshLauncherHK.exe");
			autoStartRemove(getCurrentDir() + "\\bin\\PwshLauncherHK.exe");
		}
		else
		{
			startProc("bin/PwshLauncherHK.exe");
			autoStartAdd(getCurrentDir() + "\\bin\\PwshLauncherHK.exe");
		}
	}
	return state;
}