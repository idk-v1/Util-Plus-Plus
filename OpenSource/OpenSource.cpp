#include <windows.h>
#include <shellapi.h>

int main()
{
	ShellExecute(0, 0, L"https://github.com/idk-v1/Util-Plus-Plus", 0, 0, SW_SHOW);
	return 0;
}