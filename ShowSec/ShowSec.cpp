#include <Windows.h>
#include <process.h>
#include <Tlhelp32.h>
#include <winbase.h>
#include <string>

int main(int argc, char* argv[])
{
    if (argc == 2)
    {
        DWORD showSec = argv[1][0] - '0', null;
        const wchar_t* key = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced";
        const wchar_t* value = L"ShowSecondsInSystemClock";

        RegSetKeyValueW(HKEY_CURRENT_USER, key, value, REG_DWORD, &showSec, sizeof DWORD);

        HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
        PROCESSENTRY32W pEntry;
        pEntry.dwSize = sizeof(pEntry);
        BOOL hRes = Process32FirstW(hSnapShot, &pEntry);
        while (hRes)
        {
            if (std::wstring(pEntry.szExeFile) == std::wstring(L"explorer.exe"))
            {
                HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0, pEntry.th32ProcessID);
                if (hProcess)
                {
                    TerminateProcess(hProcess, 9);
                    CloseHandle(hProcess);
                }
            }
            hRes = Process32NextW(hSnapShot, &pEntry);
        }
        CloseHandle(hSnapShot);
    }

    return 0;
}