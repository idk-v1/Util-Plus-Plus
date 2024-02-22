#include "../../Utils/File.h"

int main()
{
	std::string file;

	if (pickFile(file))
	{
		setCurrentDir(getProgDir() + "\\..\\");
		CreateShortcut(file,
			"C:\\Users\\25bsh01\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\" + 
			fileNameFromPath(file) + ".lnk");
	}

	return 0;
}