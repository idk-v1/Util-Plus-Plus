#include "../../Utils/Process.h"
#include "../../Utils/File.h"
#include "../../Utils/AutoStart.h"

int main(int argc, char* argv[])
{
	setCurrentDir(getProgDir() + "\\..\\");

	bool state = autoStartExists(getCurrentDir() + "\\bin\\PinWinHK.exe");
	if (argc == 2)
	{
		if (state)
		{
			killProc("PinWinHK.exe");
			autoStartRemove(getCurrentDir() + "\\bin\\PinWinHK.exe");
		}
		else
		{
			startProc("bin/PinWinHK.exe");
			autoStartAdd(getCurrentDir() + "\\bin\\PinWinHK.exe");
		}
	}
	return state;
}