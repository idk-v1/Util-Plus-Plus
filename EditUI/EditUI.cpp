#include <windows.h>
#include <shellapi.h>
#include "../File.h"

int main()
{
	setCurrentDir(getProgDir() + "\\..\\");

	ShellExecuteA(0, 0, "notepad.exe", "res/.ui", 0, SW_SHOW);
	return 0;
}