#include <Windows.h>
#include <string>

// These are mostly copy pasted from here:
//https://learn.microsoft.com/en-us/archive/msdn-magazine/2017/may/c-use-modern-c-to-access-the-windows-registry

DWORD RegGetDWORD(std::string key, std::string value)
{
	DWORD data{};
	DWORD dataSize = sizeof(data);
	RegGetValueA(HKEY_CURRENT_USER, key.data(), value.data(), RRF_RT_REG_DWORD, nullptr, &data, &dataSize);
	return data;
}

std::string RegGetStr(std::string key, std::string value)
{
	std::string data;
	char* dataBuf;
	DWORD dataSize = 0;
	RegGetValueA(HKEY_CURRENT_USER, key.data(), value.data(), RRF_RT_REG_SZ, nullptr, nullptr, &dataSize);
	dataBuf = new char[dataSize];
	RegGetValueA(HKEY_CURRENT_USER, key.data(), value.data(), RRF_RT_REG_SZ, nullptr, dataBuf, &dataSize);
	data = dataBuf;
	delete[] dataBuf;
	return data;
}

void RegSetDWORD(std::string key, std::string value, DWORD data)
{
	RegSetKeyValueA(HKEY_CURRENT_USER, key.data(), value.data(), REG_DWORD, &data, sizeof(data));
}

void RegSetStr(std::string key, std::string value, std::string data)
{
	RegSetKeyValueA(HKEY_CURRENT_USER, key.data(), value.data(), REG_SZ, &data[0], data.size());
}