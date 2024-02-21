#include <fstream>
#include "../Process.h"
#include "../File.h"

int main()
{
	setCurrentDir(getProgDir() + "\\..\\");

	std::ifstream src("res/default.ui");
	std::ofstream dst("res/.ui");

	if (src.is_open())
	{
		dst << src.rdbuf();
		src.close();

		killParentProc();
		startProc("Util++.exe");
	}
	dst.close();
	return 0;
}