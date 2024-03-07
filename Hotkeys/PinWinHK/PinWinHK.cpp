#include <Windows.h>
#include "../../Utils/File.h"

int main()
{
	bool ctrl, ctrlLast = 0, win, winLast = 0, t, tLast = 0;
	HWND hwnd;
	DWORD winStyle;

	setCurrentDir(getProgDir() + "\\..\\");

	while (1)
	{
		ctrl = GetAsyncKeyState(VK_CONTROL) & 0x8000;
		win = GetAsyncKeyState(VK_LWIN) & 0x8000;
		t = GetAsyncKeyState('T') & 0x8000;

		if (ctrl && win && t && !(ctrlLast && winLast && tLast))
		{
			hwnd = GetForegroundWindow();
			winStyle = GetWindowLongW(hwnd, GWL_EXSTYLE);
			if (winStyle & WS_EX_TOPMOST)
				SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			else
				SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}

		ctrlLast = ctrl;
		winLast = win;
		tLast = t;
	}

	return 0;
}