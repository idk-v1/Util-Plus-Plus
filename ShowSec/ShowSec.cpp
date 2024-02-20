#include "../Registry.h"
#include "../Process.h"

int main(int argc, char* argv[])
{
    if (argc == 2)
    {
        RegSetDWORD("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "ShowSecondsInSystemClock", argv[1][0] - '0');

        killProc("explorer.exe");
        startProc("C:/Windows/explorer.exe");
    }

    return 0;
}