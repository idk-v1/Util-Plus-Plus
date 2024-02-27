#include <Windows.h>

int main()
{
	if (MessageBoxW(NULL, L"Are you sure you want to restart?", L"Restart",
		MB_OKCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2) == IDOK)
	{
		MessageBoxW(NULL, L"restarting", 0, 0);
		InitiateShutdownA(NULL, (LPSTR)"Restarting", 5, SHUTDOWN_RESTART, SHTDN_REASON_FLAG_PLANNED);
	}
	return 0;
}