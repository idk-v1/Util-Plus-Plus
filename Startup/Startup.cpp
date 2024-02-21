#include "../UIx1.h"
#include "../Process.h"
#include <fstream>
#include <vector>

int main()
{
	sf::Vector2u winSize;
	UIx1::UI ui("res/AutoStart.ui", &winSize);

	std::ifstream listIn("data/.autostart");
	std::ofstream listOut;
	std::string data;

	UIx1::Section* sec = ui.getSectionPtr(1);

	std::vector<std::string> paths;

	int count = 0;
	if (listIn.is_open())
	{
		ui.setColor(sf::Color(0x474F57FF), sf::Color(0x171F27FF), sf::Color(0xFFFFFFFF));
		while (std::getline(listIn, data))
		{
			paths.push_back(data.substr(data.find_last_of('\\') + 1));
			sec->addButton(UIx1::vec2f(0, count), UIx1::vec2f(6, 1), ui.getStylePtr(),
				paths.back(), ui.getFontPtr(), "", 15);
		}
		listIn.close();
	}

	sf::RenderWindow win(sf::VideoMode(winSize.x, winSize.y), "Edit Startup Programs", sf::Style::Close);
	win.setFramerateLimit(20);
	while (win.isOpen())
	{
		sf::Event e;
		while (win.pollEvent(e))
			if (!e.type)
				win.close();

		ui.update(win);
		for (int i = 0; i < sec->numInputs(); i++)
			if (sec->getInput(i)->hasChanged())
			{
				listOut.open("data/.autostart");
				for (int ii = 0; ii < paths.size(); ii++)
					if (ii != i)
						listOut << paths[i] << '\n';
				listOut.close();
				win.close();
				startProc("bin/Startup.exe");
				return 0;
			}

		win.clear();
		win.draw(ui);
		win.display();
	}

	return 0;
}