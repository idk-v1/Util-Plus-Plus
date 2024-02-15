#include "../UIx1.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
	sf::Vector2u winSize;
	UIx1::UI ui("res/AutoStart.ui", &winSize);

	sf::RenderWindow win(sf::VideoMode(winSize.x, winSize.y), "Edit Startup Programs", sf::Style::Close);
	win.setFramerateLimit(20);
	while (win.isOpen())
	{
		sf::Event e;
		while (win.pollEvent(e))
			if (!e.type)
				win.close();

		ui.update(win);

		win.clear();
		win.draw(ui);
		win.display();
	}
}