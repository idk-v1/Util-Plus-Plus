#include "../../Utils/Registry.h"
#include "../../Utils/Process.h"

int main(int argc, char* argv[])
{
    bool state = RegGetDWORD("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "ShowSecondsInSystemClock");
    if (argc == 2)
    {
        RegSetDWORD("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "ShowSecondsInSystemClock", !state);
        killProc("explorer.exe");
        startProc("C:/Windows/explorer.exe");
    }
    return state;
}