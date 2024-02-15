#include <Windows.h>
#include <string>
#include <fstream>
#include <stdio.h>
#include <tlhelp32.h>
#include <Psapi.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
	std::wstring wstr;
	std::string str;
	std::ofstream listOut;
	std::ifstream listIn;

	OPENFILENAME ofn;
	wchar_t szFile[MAX_PATH];

	wchar_t currentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, currentDir);

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = 0;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = L"Executable\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn))
	{
		SetCurrentDirectory(currentDir);
		CreateDirectory(L"data", 0);

		wstr = ofn.lpstrFile;
		str = std::string(wstr.begin(), wstr.end());

		bool exists = false;
		std::string data;
		listIn.open("data/.autostart");
		if (listIn.is_open())
		{
			while (std::getline(listIn, data))
			{
				if (str == data)
				{
					exists = true;
					break;
				}
			}
			listIn.close();
		}

		if (!exists)
		{
			listOut.open("data/.autostart", std::ios::app);
			listOut << str << '\n';
			listOut.close();

			HANDLE h = NULL;
			PROCESSENTRY32 pe = { 0 };
			DWORD ppid = 0, pid = GetCurrentProcessId();
			pe.dwSize = sizeof(PROCESSENTRY32);
			h = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			if (Process32First(h, &pe))
			{
				do
				{
					if (pe.th32ProcessID == pid)
					{
						ppid = pe.th32ParentProcessID;
						break;
					}
				} while (Process32Next(h, &pe));
			}

			HANDLE hParent = OpenProcess(PROCESS_ALL_ACCESS, TRUE, ppid);
			TerminateProcess(hParent, 0);

			STARTUPINFOA info = { sizeof(info) };
			PROCESS_INFORMATION processInfo;

			if (CreateProcessA("bin/AutoStart.exe", NULL, NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo))
			{
				CloseHandle(processInfo.hProcess);
				CloseHandle(processInfo.hThread);
			}

			CloseHandle(h);
		}
	}

	return 0;
}