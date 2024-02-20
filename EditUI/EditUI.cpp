#include <windows.h>
#include <shellapi.h>

int main()
{
	ShellExecuteA(0, 0, "notepad.exe", "res/.ui", 0, SW_SHOW);
	return 0;
}