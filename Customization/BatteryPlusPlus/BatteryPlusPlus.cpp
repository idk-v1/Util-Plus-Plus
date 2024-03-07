//https://www.codeproject.com/Articles/4768/Basic-use-of-Shell-NotifyIcon-in-Win32

#include <SFML/Graphics.hpp>
#include <Windows.h>

#define TO_MICRO_SEC 1000000
#define SIZE 16

void drawNum(sf::Image& pImg, int pX, int pY, int pNum)
{
	// Top
	switch (pNum)
		case 0:case 2:case 3:case 5:case 6:case 7:case 8:case 9:
		for (int i = 0; i < 5; i++)
			pImg.setPixel(pX + i, pY, sf::Color::White);

	// Middle
	switch (pNum)
		case 2:case 3:case 4:case 5:case 6:case 8:case 9:
			for (int i = 0; i < 5; i++)
				pImg.setPixel(pX + i, pY + 4, sf::Color::White);

	// Bottom
	switch (pNum)
		case 0:case 2:case 3:case 5:case 6:case 8:case 9:
			for (int i = 0; i < 5; i++)
				pImg.setPixel(pX + i, pY + 8, sf::Color::White);

	// Top Right
	switch (pNum)
		case 0:case 1:case 2:case 3:case 4:case 7:case 8:case 9:
			for (int i = 0; i < 5; i++)
				pImg.setPixel(pX + 4, pY + i, sf::Color::White);

	// Bottom Right
	switch (pNum)
		case 0:case 1:case 3:case 4:case 5:case 6:case 7:case 8:case 9:
			for (int i = 0; i < 5; i++)
				pImg.setPixel(pX + 4, pY + 4 + i, sf::Color::White);

	// Top Left
	switch (pNum)
		case 0:case 4:case 5:case 6:case 8:case 9:
			for (int i = 0; i < 5; i++)
				pImg.setPixel(pX, pY + i, sf::Color::White);

	// Bottom Left
	switch (pNum)
		case 0:case 2:case 6:case 8:
			for (int i = 0; i < 5; i++)
				pImg.setPixel(pX, pY + 4 + i, sf::Color::White);
}

void drawSaveIcon(sf::Image& pImg)
{
	pImg.setPixel(2,10, sf::Color::Green);
	pImg.setPixel(3,10, sf::Color::Green);
	pImg.setPixel(2,11, sf::Color::Green);
	pImg.setPixel(3,11, sf::Color::Green);

	pImg.setPixel(0, 12, sf::Color::Green);
	pImg.setPixel(1, 12, sf::Color::Green);
	pImg.setPixel(2, 12, sf::Color::Green);
	pImg.setPixel(3, 12, sf::Color::Green);
	pImg.setPixel(4, 12, sf::Color::Green);
	pImg.setPixel(5, 12, sf::Color::Green);
	pImg.setPixel(0, 13, sf::Color::Green);
	pImg.setPixel(1, 13, sf::Color::Green);
	pImg.setPixel(2, 13, sf::Color::Green);
	pImg.setPixel(3, 13, sf::Color::Green);
	pImg.setPixel(4, 13, sf::Color::Green);
	pImg.setPixel(5, 13, sf::Color::Green);

	pImg.setPixel(2, 14, sf::Color::Green);
	pImg.setPixel(3, 14, sf::Color::Green);
	pImg.setPixel(2, 15, sf::Color::Green);
	pImg.setPixel(3, 15, sf::Color::Green);
}

void drawChargeIcon(sf::Image& pImg)
{
	pImg.setPixel(12, 10, sf::Color::Cyan);
	pImg.setPixel(12, 11, sf::Color::Cyan);
	pImg.setPixel(14, 10, sf::Color::Cyan);
	pImg.setPixel(14, 11, sf::Color::Cyan);

	pImg.setPixel(11, 12, sf::Color::Cyan);
	pImg.setPixel(12, 12, sf::Color::Cyan);
	pImg.setPixel(13, 12, sf::Color::Cyan);
	pImg.setPixel(14, 12, sf::Color::Cyan);
	pImg.setPixel(15, 12, sf::Color::Cyan);
	pImg.setPixel(11, 13, sf::Color::Cyan);
	pImg.setPixel(12, 13, sf::Color::Cyan);
	pImg.setPixel(13, 13, sf::Color::Cyan);
	pImg.setPixel(14, 13, sf::Color::Cyan);
	pImg.setPixel(15, 13, sf::Color::Cyan);

	pImg.setPixel(12, 14, sf::Color::Cyan);
	pImg.setPixel(13, 14, sf::Color::Cyan);
	pImg.setPixel(14, 14, sf::Color::Cyan);
	pImg.setPixel(13, 15, sf::Color::Cyan);

}

int main()
{
	sf::RenderWindow win; 
	win.create(sf::VideoMode(0, 0), "");
	win.setVisible(false);

	sf::Clock clock;
	int deltaTime = 5 * TO_MICRO_SEC;

	NOTIFYICONDATAA notifIcon{ 0 };
	notifIcon.cbSize = sizeof(NOTIFYICONDATA);
	notifIcon.uID = 2024;
	notifIcon.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	notifIcon.hWnd = win.getSystemHandle();

	Shell_NotifyIconA(NIM_ADD, &notifIcon);

	sf::Image img;
	HBITMAP bitmap;
	ICONINFO ii;
	HICON hIcon;

	Shell_NotifyIconA(NIM_MODIFY, &notifIcon);

	while (win.isOpen())
	{
		sf::Event e;
		while (win.pollEvent(e))
			if (!e.type)
				win.close();
		
		deltaTime += clock.restart().asMicroseconds();
		while (deltaTime >= 5 * TO_MICRO_SEC)
		{
			deltaTime -= 5 * TO_MICRO_SEC;

			SYSTEM_POWER_STATUS power;
			GetSystemPowerStatus(&power);

			img.create(SIZE, SIZE, sf::Color::Black);
			if (power.BatteryLifePercent != 255)
			{
				drawNum(img, 0, 0, power.BatteryLifePercent > 99 ? 1 : -1);
				drawNum(img, 3, 0, (power.BatteryLifePercent / 10) % 10);
				drawNum(img, 10,0, power.BatteryLifePercent % 10);
			}
			if (power.SystemStatusFlag)
				drawSaveIcon(img);
			if (power.ACLineStatus)
				drawChargeIcon(img);

			bitmap = CreateBitmap(SIZE, SIZE, 1, 32, img.getPixelsPtr());
			ii = { 1, 0, 0, bitmap, bitmap };
			hIcon = CreateIconIndirect(&ii);
			notifIcon.hIcon = hIcon;
			Shell_NotifyIconA(NIM_MODIFY, &notifIcon);
			DestroyIcon(hIcon);
			DeleteObject(bitmap);
		}
	}

	Shell_NotifyIconA(NIM_DELETE, &notifIcon);
	return 0;
}