#include <windows.h>
#include <urlmon.h>
#pragma comment(lib,"urlmon.lib")

#include "../../Utils/File.h"
#include "../../Utils/Process.h"
#include "../../Utils/miniz.c"

int main()
{
    setCurrentDir(getProgDir() + "\\..\\");

    if (!URLDownloadToFileA(0,
        "https://github.com/idk-v1/Util-Plus-Plus/releases/latest/download/util-plus-plus.zip",
        "temp.zip",
        0, NULL))
    {
        killParentProc();

        std::string file;
        mz_zip_archive zip;
        memset(&zip, 0, sizeof(zip));
        mz_zip_reader_init_file(&zip, "temp.zip", 0);
        
        for (int i = 0; i < mz_zip_reader_get_num_files(&zip); i++)
        {
            mz_zip_archive_file_stat file_stat;
            if (!mz_zip_reader_file_stat(&zip, i, &file_stat))
                break;

            file = file_stat.m_filename;
            if (file.find('/') != std::string::npos)
                mkDir(file.substr(0, file.find('/')));
            mz_zip_reader_extract_file_to_file(&zip, file_stat.m_filename,
                std::string(getCurrentDir() + "\\" + file_stat.m_filename).data(), 0);
        }
        mz_zip_reader_end(&zip);
        remove("temp.zip");

        startProc("Util-Plus-Plus.exe");
    }

	return 0;
}