#include "../Registry.h"
#include "../File.h"

int main()
{
    std::string str = RegGetStr("Environment", "UserInitMprLogonScript");
    std::string path = getCurrentDir() + "\\bin\\StartupRunner.exe";
       
    return str == path;
}