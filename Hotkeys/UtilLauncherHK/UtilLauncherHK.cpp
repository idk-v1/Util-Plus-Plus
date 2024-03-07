#include <Windows.h>
#include "../../Utils/Process.h"
#include "../../Utils/File.h"

int main()
{
	bool ctrl, ctrlLast = 0, win, winLast = 0, e, eLast = 0;

	setCurrentDir(getProgDir() + "\\..\\");

	while (1)
	{
		ctrl = GetAsyncKeyState(VK_CONTROL) & 0x8000;
		win = GetAsyncKeyState(VK_LWIN) & 0x8000;
		e = GetAsyncKeyState('E') & 0x8000;

		if (ctrl && win && e && !(ctrlLast && winLast && eLast))
			startProc("Util-Plus-Plus.exe");

		ctrlLast = ctrl;
		winLast = win;
		eLast = e;
	}

	return 0;
}