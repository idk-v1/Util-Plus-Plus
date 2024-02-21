#include "../File.h"
#include "../Registry.h"

int main(int argc, char* argv[])
{
    std::string autoStart;
    if (argc == 2)
    {
        setCurrentDir(getProgDir() + "\\..\\");

        if (argv[1][0] - '0')
            autoStart = getCurrentDir() + "\\bin\\StartupRunner.exe";

        RegSetStr("Environment", "UserInitMprLogonScript", autoStart);
    }

    return 0;
}