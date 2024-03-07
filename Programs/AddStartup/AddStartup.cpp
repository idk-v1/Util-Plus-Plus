#include "../../Utils/File.h"
#include "../../Utils/Process.h"
#include "../../Utils/Autostart.h"
#include <fstream>

int main()
{
	std::string str;
	std::ofstream listOut;
	std::ifstream listIn;

	if (pickFile(str))
	{
		setCurrentDir(getProgDir() + "\\..\\");

		if (!autoStartExists(str))
		{
			autoStartAdd(str);

			// reload program list
			killParentProc();
			startProc("bin/Startup.exe");
		}
	}

	return 0;
}