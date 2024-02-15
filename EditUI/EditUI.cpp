#include <windows.h>
#include <shellapi.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
	ShellExecute(0, 0, L"notepad.exe", L"res/.ui", 0, SW_SHOW);
	return 0;
}