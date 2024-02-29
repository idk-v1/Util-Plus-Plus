//https://www.codeproject.com/Articles/4768/Basic-use-of-Shell-NotifyIcon-in-Win32

#include <SFML/Graphics.hpp>
#include <Windows.h>

#define TO_MICRO 1000000
#define SIZE 64

sf::Image createImage()
{
	sf::RenderTexture tex;
	tex.create(SIZE, SIZE);

	sf::RectangleShape rect(sf::Vector2f(SIZE, SIZE));
	rect.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256, 255));
	tex.draw(rect);

	return tex.getTexture().copyToImage();
}

void render(NOTIFYICONDATAA& pNotifIcon)
{
	sf::Image icon = createImage();

	HBITMAP bitmap = CreateBitmap(SIZE, SIZE, 1, 32, icon.getPixelsPtr());
	ICONINFO ii = { TRUE, 0, 0, bitmap, bitmap };
	HICON hIcon = CreateIconIndirect(&ii);

	pNotifIcon.hIcon = hIcon;
	Shell_NotifyIconA(NIM_MODIFY, &pNotifIcon);
	DestroyIcon(hIcon);
	DeleteObject(bitmap);
}

int main()
{
	sf::RenderWindow win; 
	win.create(sf::VideoMode(0, 0), "");
	win.setVisible(false);

	sf::Clock clock;
	int deltaTime = 0;

	NOTIFYICONDATAA notifIcon{ 0 };
	notifIcon.cbSize = sizeof(NOTIFYICONDATA);
	notifIcon.uID = 2024;
	notifIcon.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	notifIcon.hWnd = win.getSystemHandle();

	Shell_NotifyIconA(NIM_ADD, &notifIcon);

	render(notifIcon);

	while (win.isOpen())
	{
		sf::Event e;
		while (win.pollEvent(e))
			if (!e.type)
				win.close();
		
		deltaTime += clock.restart().asMicroseconds();
		while (deltaTime >= 5 * TO_MICRO)
		{
			deltaTime -= 5 * TO_MICRO;
			render(notifIcon);
		}
	}

	Shell_NotifyIconA(NIM_DELETE, &notifIcon);

	return 0;
}