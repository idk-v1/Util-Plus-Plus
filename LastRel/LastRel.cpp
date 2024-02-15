#include <windows.h>
#include <shellapi.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	ShellExecute(0, 0, L"https://github.com/idk-v1/Util-Plus-Plus/releases/latest", 0, 0, SW_SHOW);
	return 0;
}