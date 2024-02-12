#include "UIx1.h"


int main()
{
	sf::Vector2u winSize;
	UIx1::UI ui(".ui", &winSize);

	sf::RenderWindow win(sf::VideoMode(winSize.x, winSize.y), "UI");
	while (win.isOpen())
	{
		sf::Event e;
		while (win.pollEvent(e))
			if (!e.type)
				win.close();

		win.clear();

		win.draw(ui);

		win.display();
	}
}