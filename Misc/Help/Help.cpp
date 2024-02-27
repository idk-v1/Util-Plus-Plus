#include "../../Utils/UIx1.h"


int main()
{
	sf::Vector2u winSize;
	UIx1::UI ui("res/help.ui", &winSize);

	sf::RenderWindow win(sf::VideoMode(winSize.x, winSize.y), "Help", sf::Style::Close);
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