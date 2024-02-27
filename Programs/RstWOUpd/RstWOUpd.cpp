#include <Windows.h>

int main()
{
	if (MessageBoxW(NULL, L"Are you sure you want to restart?", L"Restart",
		MB_OKCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2) == IDOK)
	{
		MessageBoxW(NULL, L"restarting", 0, 0);

        HANDLE hToken = NULL;
        LUID luid;
        TOKEN_PRIVILEGES tp;

        OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken);
        LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &luid);

        tp.PrivilegeCount = 1;
        tp.Privileges[0].Luid = luid;
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
        AdjustTokenPrivileges(hToken, false, &tp, sizeof(tp), NULL, 0);

       //InitiateSystemShutdownA(NULL, NULL, 0, true, true);
	}
	return 0;
}