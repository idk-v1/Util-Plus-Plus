#include <windows.h>
#include <shellapi.h>

int main()
{
	ShellExecute(0, 0, L"notepad.exe", L".ui", 0, SW_SHOW);
	return 0;
}