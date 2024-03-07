#include "../../Utils/Process.h"
#include "../../Utils/File.h"
#include "../../Utils/AutoStart.h"

int main(int argc, char* argv[])
{
	setCurrentDir(getProgDir() + "\\..\\");

	bool state = autoStartExists(getCurrentDir() + "\\bin\\ProcExpLauncherHK.exe");
	if (argc == 2)
	{
		if (state)
		{
			killProc("ProcExpLauncherHK.exe");
			autoStartRemove(getCurrentDir() + "\\bin\\ProcExpLauncherHK.exe");
		}
		else
		{
			startProc("bin/ProcExpLauncherHK.exe");
			autoStartAdd(getCurrentDir() + "\\bin\\ProcExpLauncherHK.exe");
		}
	}
	return state;
}