#include "../../Utils/File.h"
#include "../../Utils/Registry.h"

int main(int argc, char* argv[])
{
    setCurrentDir(getProgDir() + "\\..\\");
    std::string str = RegGetStr("Environment", "UserInitMprLogonScript");
    std::string path = getCurrentDir() + "\\bin\\StartupRunner.exe";

    bool state = (str == path);
    if (argc == 2)
    {
        if (state)
            RegSetStr("Environment", "UserInitMprLogonScript", "");
        else
            RegSetStr("Environment", "UserInitMprLogonScript", getCurrentDir() + "\\bin\\StartupRunner.exe");
    }
    return state;
}