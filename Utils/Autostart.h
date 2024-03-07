#pragma once

#include "File.h"
#include <fstream>

bool autoStartExists(std::string pPath)
{
	std::string data;
	std::ifstream listIn("data/.autostart");
	if (listIn.is_open())
	{
		while (std::getline(listIn, data))
			if (pPath == data)
				return true;
		listIn.close();
	}
	return false;
}

void autoStartAdd(std::string pPath)
{
	mkDir("data");
	std::ofstream listOut("data/.autostart", std::ios::app);
	listOut << pPath << '\n';
	listOut.close();
}

void autoStartRemove(std::string pPath)
{
	std::string data;
	std::ofstream temp("data/temp");
	std::ifstream listIn("data/.autostart");

	while (std::getline(listIn, data))
		if (data != pPath)
			temp << data << '\n';

	listIn.close();
	temp.close();

	remove("data/.autostart");
	rename("data/temp", "data/.autostart");
}