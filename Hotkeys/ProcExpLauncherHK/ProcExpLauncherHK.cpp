#include <Windows.h>
#include "../../Utils/Process.h"
#include "../../Utils/File.h"

int main()
{
	bool ctrl, ctrlLast = 0, shift, shiftLast = 0, esc, escLast = 0;

	setCurrentDir(getProgDir() + "\\..\\");

	while (1)
	{
		ctrl = GetAsyncKeyState(VK_CONTROL) & 0x8000;
		shift = GetAsyncKeyState(VK_SHIFT) & 0x8000;
		esc = GetAsyncKeyState(VK_ESCAPE) & 0x8000;

		if (ctrl && shift && esc && !(ctrlLast && shiftLast && escLast))
			startProc("bin\\procexp.exe");

		ctrlLast = ctrl;
		shiftLast = shift;
		escLast = esc;
	}

	return 0;
}