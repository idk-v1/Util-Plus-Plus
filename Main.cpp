#include "Utils/UIx1.h"
#include "Utils/File.h"

#define VERSION_MAJOR 1 // Compatibility
#define VERSION_MINOR 7 // Feature
#define VERSION_PATCH 0 // Bug Fix
//#define DEBUG 1			// Work in Progress

int main()
{
	setCurrentDir(getProgDir());
	sf::Vector2u winSize;
	UIx1::UI ui("res/.ui", &winSize);

	std::string version = "v";
	version += VERSION_MAJOR + '0';
	version += '.';
	version += VERSION_MINOR + '0';
	version += '.';
	version += VERSION_PATCH + '0';
#ifdef DEBUG
		version += " - Debug";
#endif


	sf::RenderWindow win(sf::VideoMode(winSize.x, winSize.y), "Util-Plus-Plus - " + version, sf::Style::Close);
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