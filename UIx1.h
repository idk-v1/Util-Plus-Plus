#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <fstream>

namespace UIx1
{
	class RoundedRect : public sf::Drawable
	{
	public:
		RoundedRect() {}
		RoundedRect(int pX, int pY, int pW, int pH, float pRadius)
		{
			x = pX;
			y = pY;
			w = pW;
			h = pH;
			rad = pRadius;

			wRect.setSize(sf::Vector2f(w, h - rad * 2));
			wRect.setPosition(x, y + rad);
			hRect.setSize(sf::Vector2f(w - rad * 2, h));
			hRect.setPosition(x + rad, y);

			tlCirc.setRadius(rad);
			tlCirc.setPosition(x, y);
			trCirc.setRadius(rad);
			trCirc.setPosition(x + w - rad * 2, y);
			brCirc.setRadius(rad);
			brCirc.setPosition(x + w - rad * 2, y + h - rad * 2);
			blCirc.setRadius(rad);
			blCirc.setPosition(x, y + h - rad * 2);
		}

		void setColor(sf::Color color)
		{
			wRect.setFillColor(color);
			hRect.setFillColor(color);
			tlCirc.setFillColor(color);
			trCirc.setFillColor(color);
			brCirc.setFillColor(color);
			blCirc.setFillColor(color);
		}

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(wRect, states);
			target.draw(hRect, states);
			target.draw(tlCirc, states);
			target.draw(trCirc, states);
			target.draw(brCirc, states);
			target.draw(blCirc, states);
		}

		sf::RectangleShape wRect, hRect;
		sf::CircleShape tlCirc, trCirc, brCirc, blCirc;

		int x, y, w, h;
		float rad;
	};

	class Input : public sf::Drawable 
	{
	public:
		Input() {}
		Input(int pX, int pY, int pW, int pH, int pRadius)
		{
			rect = RoundedRect(pX, pY, pW, pH, pRadius);
		}

	protected:
		RoundedRect rect;
	};

	class Button : public Input
	{
	public:
		Button() {}
		Button(int pX, int pY, int pW, int pH, std::string pLabel, std::string pExec, sf::Font* pFontPtr)
		{
			
		}

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(rect, states);
		}
	};

	class Toggle : public Input
	{
	public:
		Toggle() {}

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{

		}
	};

	class Section : public sf::Drawable
	{
	public:
		Section() {}
		Section(int pX, int pY, int pW, int pH, std::string pLabel, sf::Font* pFontPtr)
		{
			x = pX;
			y = pY;
			w = pW;
			h = pH + 1;
			label = pLabel;

			labelRect = RoundedRect(scale * x + space, scale * y + space, scale * w - space * 2, scale - space * 2, round - space);
			labelRect.setColor(labelColor);
			bodyRect = RoundedRect(scale * x + space, scale * y + space, scale * w - space * 2, scale * h - space * 2, round - space);
			bodyRect.setColor(bodyColor);

			text.setFont(*pFontPtr);
			text.setString(label);
			text.setPosition(x * scale + space + ((scale * w - space * 2) - text.getLocalBounds().width) / 2.f, y * scale + space);
		}

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(bodyRect, states);
			target.draw(labelRect, states);
			target.draw(text, states);
		}

		std::vector<Input*> inputs;
		RoundedRect labelRect, bodyRect;
		std::string label;
		sf::Text text;
		sf::Color labelColor = sf::Color(0x2F373FFF);
		sf::Color bodyColor = sf::Color(0x1F272FFF);
		int x, y, w, h;
		int scale = 50, round = 15, space = 2;
	};

	class UI : public sf::Drawable
	{
	public:
		UI() {}
		UI(std::string pFilename, std::string pFontName, sf::Vector2u* winSize = nullptr)
		{
			font.loadFromFile(pFontName);
			loadFile(pFilename, winSize);
		}

		void parseLines(std::vector<std::string>& lines, sf::Vector2u* winSize)
		{
			int x, y, w, h;
			std::string str;
			for (auto& line : lines)
			{
				switch (line.at(0))
				{
				case 'S':
				case 's':
					if (lines.size() > 10)
					{
						x = 10 * (line.at(1) - '0') + (line.at(2) - '0');
						y = 10 * (line.at(3) - '0') + (line.at(4) - '0');
						w = 10 * (line.at(5) - '0') + (line.at(6) - '0');
						h = 10 * (line.at(7) - '0') + (line.at(8) - '0');

						if (line.size() - 10 > 10 * (line.at(9) - '0') + (line.at(10) - '0'))
							str = line.substr(11, 10 * (line.at(9) - '0') + (line.at(10) - '0'));

						sections.push_back(Section(x, y, w, h, str, &font));
					}
					break;
					
				case 'B':
				case 'b':
					break;

				case 'T':
				case 't':
					break;

				case 'Z':
				case 'z':
					if (winSize != nullptr && line.size() > 8)
					{
						winSize->x = 1000 * (line.at(1) - '0') + 100 * (line.at(2) - '0') + 10 * (line.at(3) - '0') + (line.at(4) - '0');
						winSize->y = 1000 * (line.at(5) - '0') + 100 * (line.at(6) - '0') + 10 * (line.at(7) - '0') + (line.at(8) - '0');
					}
					break;
				}
			}
		}

		bool loadFile(std::string pFileName, sf::Vector2u* winSize)
		{
			std::ifstream file(pFileName);
			std::string data, clean;
			std::vector<std::string> lines;
			int strLen;
			bool inQuote = false;
			
			if (file.is_open())
			{
				while (std::getline(file, data))
				{
					clean.clear();
					for (char c : data)
					{
						if (c == '"')
						{
							inQuote = !inQuote;
							if (inQuote)
							{
								clean.push_back('0');
								clean.push_back('0');
								strLen = 0;
							}
							else
							{
								clean.at(clean.size() - 1 - strLen) += strLen % 10;
								clean.at(clean.size() - 2 - strLen) += strLen / 10;
							}
						}
						else if (c != '\t' && (c != ' ' || inQuote))
						{
							clean.push_back(c);
							if (inQuote)
								strLen++;
						}
					}
					if (clean.size() && clean.at(0) != '#')
						lines.push_back(clean);
				}
				file.close();
				parseLines(lines, winSize);
				return true;
			}
			return false;
		}

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			for (auto& section : sections)
				target.draw(section, states);
		}

		std::vector<Section> sections;
		sf::Font font;
	};

}