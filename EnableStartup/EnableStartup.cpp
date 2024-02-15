#include <Windows.h>
#include <process.h>
#include <Tlhelp32.h>
#include <winbase.h>
#include <string>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
    std::string autoStart;
    if (__argc == 2)
    {
        char currentDir[MAX_PATH];
        GetCurrentDirectoryA(MAX_PATH, currentDir);
        DWORD enable = (__argv[1][0] - '0');
        const char* key = "Environment";
        const char* value = "UserInitMprLogonScript";

        if (enable)
            autoStart = std::string(currentDir) + "\\bin\\StartupRunner.exe";

        RegSetKeyValueA(HKEY_CURRENT_USER, key, value, REG_SZ, autoStart.data(), autoStart.size());
    }

    return 0;
}