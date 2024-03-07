#pragma once

#include <Windows.h>
#include <string>
#include <tlhelp32.h>

DWORD getProcID(std::string pProc)
{
	std::wstring wProc = std::wstring(pProc.begin(), pProc.end());
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
	DWORD pid = 0;
	PROCESSENTRY32W pEntry{};
	pEntry.dwSize = sizeof(pEntry);
	BOOL hRes = Process32First(hSnapShot, &pEntry);
	while (hRes)
	{
		if (std::wstring(pEntry.szExeFile) == wProc)
		{
			pid = pEntry.th32ProcessID;
			break;
		}
		hRes = Process32NextW(hSnapShot, &pEntry);
	}
	CloseHandle(hSnapShot);

	return pid;
}

void killProc(std::string pProc)
{
	DWORD pid = getProcID(pProc);
	HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0, pid);
	if (hProcess)
	{
		TerminateProcess(hProcess, 0);
		CloseHandle(hProcess);
	}
}

void killParentProc()
{
	PROCESSENTRY32 pe = { 0 };
	DWORD ppid = 0, pid = GetCurrentProcessId();
	pe.dwSize = sizeof(PROCESSENTRY32);
	HANDLE hParent, handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (Process32First(handle, &pe))
	{
		do
		{
			if (pe.th32ProcessID == pid)
			{
				ppid = pe.th32ParentProcessID;
				break;
			}
		} while (Process32Next(handle, &pe));
	}

	hParent = OpenProcess(PROCESS_ALL_ACCESS, TRUE, ppid);
	TerminateProcess(hParent, 0);
	CloseHandle(hParent);
	CloseHandle(handle);
}

bool startProc(std::string pPath)
{
	STARTUPINFOA info = { sizeof(info) };
	PROCESS_INFORMATION processInfo;

	if (CreateProcessA(pPath.data(), NULL, NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo))
	{
		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);
		return true;
	}

	return false;
}

bool startProcWait(std::string pPath, int& pExit)
{
	STARTUPINFOA info = { sizeof(info) };
	PROCESS_INFORMATION processInfo;
	DWORD exit;

	if (CreateProcessA(pPath.data(), NULL, NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo))
	{
		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);
		WaitForSingleObject(processInfo.hProcess, INFINITE);
		GetExitCodeProcess(processInfo.hProcess, &exit);
		pExit = exit;
		return true;
	}

	return false;
}