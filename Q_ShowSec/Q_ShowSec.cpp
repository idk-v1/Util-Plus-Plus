#include <Windows.h>
#include <string>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
    unsigned long long showSec;
    unsigned long null;
    const char* key = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced";
    const char* value = "ShowSecondsInSystemClock";

    RegGetValueA(HKEY_CURRENT_USER, key, value, RRF_RT_ANY, NULL, &showSec, &null);
    return showSec;
}