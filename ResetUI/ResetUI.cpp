#include <fstream>
#include <Windows.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <Psapi.h>

int main()
{
	std::ifstream src("default.ui");
	std::ofstream dst(".ui");

	if (src.is_open())
	{
		dst << src.rdbuf();
		src.close();

        HANDLE h = NULL;
        PROCESSENTRY32 pe = { 0 };
        DWORD ppid = 0, pid = GetCurrentProcessId();
        pe.dwSize = sizeof(PROCESSENTRY32);
        h = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (Process32First(h, &pe))
        {
            do
            {
                if (pe.th32ProcessID == pid)
                {
                    ppid = pe.th32ParentProcessID;
                    break;
                }
            } while (Process32Next(h, &pe));
        }

        HANDLE hParent = OpenProcess(PROCESS_ALL_ACCESS, TRUE, ppid);
        TerminateProcess(hParent, 0);

		STARTUPINFOA info = { sizeof(info) };
		PROCESS_INFORMATION processInfo;

		if (CreateProcessA("Util++.exe", NULL, NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo))
		{
			CloseHandle(processInfo.hProcess);
			CloseHandle(processInfo.hThread);
		}
		else
			printf("Failed to start \"Util++.exe\"\n");

        CloseHandle(h);
	}
	else
		printf("Failed to open \"default.ui\"\n");
	dst.close();
	return 0;
}