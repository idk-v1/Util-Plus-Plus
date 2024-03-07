#include <Windows.h>
#include "../../Utils/Process.h"
#include "../../Utils/File.h"

int main()
{
	bool ctrl, ctrlLast = 0, alt, altLast = 0, t, tLast = 0;

	setCurrentDir(getProgDir() + "\\..\\");

	while (1)
	{
		ctrl = GetAsyncKeyState(VK_CONTROL) & 0x8000;
		alt = GetAsyncKeyState(VK_MENU) & 0x8000;
		t = GetAsyncKeyState('T') & 0x8000;

		if (ctrl && alt && t && !(ctrlLast && altLast && tLast))
			startProc("bin\\powershell.exe");

		ctrlLast = ctrl;
		altLast = alt;
		tLast = t;

		Sleep(10);
	}

	return 0;
}