#include <windows.h>
#include <shellapi.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	ShellExecute(0, 0, L"notepad.exe", L".ui", 0, SW_SHOW);
	return 0;
}