#include <Windows.h>
#include <string>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
    char currentDir[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, currentDir);

    // I know the max registry string length is somewhere around 1MB, 
    // but this stores a path which has a max length of 260
    char logonScript[MAX_PATH];
    unsigned long size = MAX_PATH;

    const char* key = "Environment";
    const char* value = "UserInitMprLogonScript";

    int error = RegGetValueA(HKEY_CURRENT_USER, key, value, RRF_RT_ANY, NULL, &logonScript, &size);
    std::string str(logonScript), autoStart(std::string(currentDir) + "\\bin\\StartupRunner.exe");

    return str == autoStart;
}