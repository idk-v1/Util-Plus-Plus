//https://www.codeproject.com/Articles/4768/Basic-use-of-Shell-NotifyIcon-in-Win32

#include <SFML/Graphics.hpp>
#include <Windows.h>

int main()
{
	sf::RenderWindow win; 
	win.create(sf::VideoMode(0, 0), "");
	win.setVisible(false);

	sf::Image icon;
	// SFML swaps red and blue channels for some reason
	icon.create(256, 256, sf::Color::Red);

	//icon.loadFromFile("res/test.png");
	HBITMAP bitmap = CreateBitmap(256, 256, 1, 32, icon.getPixelsPtr());
	ICONINFO ii = { TRUE, 0, 0, bitmap, bitmap };
	HICON hIcon = CreateIconIndirect(&ii);

	NOTIFYICONDATAA notifIcon{ 0 };
	notifIcon.cbSize = sizeof(NOTIFYICONDATA);
	notifIcon.uID = 2024;
	notifIcon.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	notifIcon.hIcon = hIcon;
	notifIcon.hWnd = win.getSystemHandle();

	Shell_NotifyIconA(NIM_ADD, &notifIcon);

	while (win.isOpen())
	{
		sf::Event e;
		while (win.pollEvent(e))
			if (!e.type)
				win.close();
	}

	return 0;
}