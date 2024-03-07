// Thank you Ciantic!
// https://stackoverflow.com/a/25812667

#include <Windows.h>

int main()
{
	ShellExecuteA(NULL, "taskbarunpin", "C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\Outlook.lnk", NULL, NULL, 0);
	ShellExecuteA(NULL, "taskbarunpin", "C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\Google Chrome.lnk", NULL, NULL, 0);
	return 0;
}