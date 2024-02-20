#include "../Registry.h"

int main()
{
    return RegGetDWORD("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "ShowSecondsInSystemClock");
}