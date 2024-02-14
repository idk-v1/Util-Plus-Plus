#include <Windows.h>
#include <string>

int main()
{
    DWORD showSec = 0, null;
    const wchar_t* key = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced";
    const wchar_t* value = L"ShowSecondsInSystemClock";

    RegGetValueW(HKEY_CURRENT_USER, key, value, RRF_RT_DWORD, NULL, &showSec, &null);
    return showSec;
}