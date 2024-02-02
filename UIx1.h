#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <fstream>

namespace UIx1
{
	using vec2 = sf::Vector2f;

	struct Style
	{
		Style() {}
		Style(int pScale, int pRad, int pSpace)
		{
			scale = pScale;
			rad = pRad;
			space = pSpace;
		}

		int scale, rad, space;
	};

	struct Color
	{
		Color() {}
		Color(sf::Color pFront, sf::Color pBack, sf::Color pText)
		{
			front = pFront;
			back = pBack;
			text = pText;
		}

		sf::Color front, back, text;
	};

	class RoundedRect : public sf::Drawable
	{
	public:
		RoundedRect() {}
		RoundedRect(vec2 pPos, vec2 pSize, Style* pStylePtr, int pSpaceLvl = 1)
		{
			pos = pPos;
			size = pSize;
			st = pStylePtr;
			spaceLvl = pSpaceLvl;

			wRect.setSize(
				vec2(size.x * st->scale - 2 * st->space * spaceLvl,
				size.y * st->scale - 2 * st->rad - 2 * st->space * spaceLvl));
			wRect.setPosition(pos.x * st->scale + st->space * spaceLvl,
				pos.y * st->scale + st->rad + st->space * spaceLvl);

			hRect.setSize(
				vec2(size.x * st->scale - 2 * st->rad - 2 * st->space * spaceLvl,
				size.y * st->scale - 2 * st->space * spaceLvl));
			hRect.setPosition(pos.x * st->scale + st->rad + st->space * spaceLvl,
				pos.y * st->scale + st->space * spaceLvl);

			tlCirc.setRadius(st->rad - st->space * spaceLvl);
			tlCirc.setPosition(pos.x * st->scale + st->space * spaceLvl,
				pos.y * st->scale + st->space * spaceLvl);

			trCirc.setRadius(st->rad - st->space * spaceLvl);
			trCirc.setPosition(
				(pos.x + size.x) * st->scale - 2 * st->rad + st->space * spaceLvl,
				pos.y * st->scale + st->space * spaceLvl);

			brCirc.setRadius(st->rad - st->space * spaceLvl);
			brCirc.setPosition(
				(pos.x + size.x) * st->scale - 2 * st->rad + st->space * spaceLvl,
				(pos.y + size.y) * st->scale - 2 * st->rad + st->space * spaceLvl);

			blCirc.setRadius(st->rad - st->space * spaceLvl);
			blCirc.setPosition(pos.x * st->scale + st->space * spaceLvl,
				(pos.y + size.y) * st->scale - 2 * st->rad + st->space * spaceLvl);
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
		void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(wRect,  states);
			target.draw(hRect,  states);
			target.draw(tlCirc, states);
			target.draw(trCirc, states);
			target.draw(brCirc, states);
			target.draw(blCirc, states);
		}

		sf::RectangleShape wRect, hRect;
		sf::CircleShape tlCirc, trCirc, brCirc, blCirc;

		Style* st;
		vec2 pos, size;
		int spaceLvl = 1;
	};

	class Input : public sf::Drawable 
	{
	public:
		Input() {}
		Input(vec2 pPos, vec2 pSize, Style* pStylePtr)
		{
			pos = pPos;
			size = pSize;
			st = pStylePtr;

			rect = RoundedRect(pos, size, st);
		}

	protected:
		Style* st;
		vec2 pos, size;
		RoundedRect rect;

	private:
		virtual void draw(sf::RenderTarget& target, 
			sf::RenderStates states) const {}
	};

	class Button : public Input
	{
	public:
		Button() {}
		Button(vec2 pPos, vec2 pSize, Style* pStylePtr, std::string pLabelStr, 
			sf::Font* pFontPtr) : Input(pPos, pSize, pStylePtr)
		{

		}

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(rect, states);
		}

		RoundedRect labelRect;
	};

	class Toggle : public Input
	{
	public:
		Toggle() {}
		Toggle(vec2 pPos, vec2 pSize, Style* pStylePtr, std::string pLabelStr, 
			sf::Font* pFontPtr) : Input(pPos, pSize, pStylePtr)
		{

		}

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(rect, states);
		}
	};

	class Textbox : public Input
	{
	public:
		Textbox() {}
		Textbox(vec2 pPos, vec2 pSize, Style* pStylePtr, std::string pLabelStr, 
			sf::Font* pFontPtr) : Input(pPos, pSize, pStylePtr)
		{

		}

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(rect, states);
		}
	};

	class Section : public sf::Drawable
	{
	public:
		Section() {}
		Section(vec2 pPos, vec2 pSize, Style* pStylePtr, std::string pLabelStr,
			sf::Font* pFontPtr)
		{
			pos = pPos;
			size = vec2(pSize.x, pSize.y + 1);
			st = pStylePtr;

			labelStr = pLabelStr;
			fontPtr = pFontPtr;

			label.setFont(*fontPtr);
			label.setString(labelStr);
			label.setPosition(pos.x * st->scale + 
				(size.x * st->scale - label.getLocalBounds().width) / 2.f, 
				pos.y * st->scale + st->space);

			labelRect = RoundedRect(pos, vec2(size.x, 1), st);
			bodyRect = RoundedRect(pos, size, st);

			labelRect.setColor(labelColor);
			bodyRect.setColor(bodyColor);
		}

		void addButton(vec2 pPos, vec2 pSize, Style* pStylePtr, 
			std::string str, sf::Font* pFontPtr)
		{
			inputs.push_back(new Button(vec2(pPos.x + pos.x, pPos.y + pos.y + 1), 
				pSize, pStylePtr, str, pFontPtr));
		}

		void addToggle(vec2 pPos, vec2 pSize, Style* pStylePtr,
			std::string str, sf::Font* pFontPtr)
		{
			inputs.push_back(new Toggle(vec2(pPos.x + pos.x, pPos.y + pos.y + 1), 
				pSize, pStylePtr, str, pFontPtr));
		}

		void addTextbox(vec2 pPos, vec2 pSize, Style* pStylePtr,
			std::string str, sf::Font* pFontPtr)
		{
			inputs.push_back(new Textbox(vec2(pPos.x + pos.x, pPos.y + pos.y + 1),
				pSize, pStylePtr, str, pFontPtr));
		}

		Input* getInput(int pIndex)
		{
			if (pIndex >= 0 && pIndex < inputs.size())
				return inputs[pIndex];
			return nullptr;
		}

		int numInputs()
		{
			return inputs.size();
		}

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(bodyRect, states);
			target.draw(labelRect, states);
			target.draw(label, states);

			for (auto& input : inputs)
				target.draw(*input, states);
		}

		sf::Color labelColor = sf::Color(0x2F373FFF);
		sf::Color bodyColor = sf::Color(0x1F272FFF);

		std::vector<Input*> inputs;

		vec2 pos, size;
		RoundedRect labelRect, bodyRect;
		Style* st;

		std::string labelStr;
		sf::Font* fontPtr;
		sf::Text label;
	};

	class UI : public sf::Drawable
	{
	public:
		UI() {}
		UI(std::string pFilename, sf::Vector2u* winSize = nullptr)
		{
			loadFile(pFilename, winSize);
		}

		void addSection(vec2 pPos, vec2 pSize, Style* pStylePtr, 
			std::string pString, sf::Font* pFontPtr)
		{
			sections.push_back(Section(pPos, pSize, 
				pStylePtr, pString, pFontPtr));
		}

		Section* getSectionPtr(int pIndex)
		{
			if (pIndex >= 0 && pIndex < sections.size())
				return &sections[pIndex];
			return nullptr;
		}

		int numSection()
		{
			return sections.size();
		}

		void parseLines(std::vector<std::string>& lines, sf::Vector2u* winSize)
		{
			int x, y, w, h;
			int strLen, strPos;
			std::string str, str2;

			for (auto& line : lines)
				if (line.at(0) == '?')
				{
					if (winSize != nullptr && line.size() > 18)
					{
						winSize->x =
							1000 * (line.at(1) - '0') +
							100 * (line.at(2) - '0') +
							10 * (line.at(3) - '0') +
							1 * (line.at(4) - '0');
						winSize->y =
							1000 * (line.at(5) - '0') +
							100 * (line.at(6) - '0') +
							10 * (line.at(7) - '0') +
							1 * (line.at(8) - '0');
						style.scale =
							100 * (line.at(9) - '0') +
							10 * (line.at(10) - '0') +
							1 * (line.at(11) - '0');
						style.rad =
							100 * (line.at(12) - '0') +
							10 * (line.at(13) - '0') +
							1 * (line.at(14) - '0');
						style.space =
							10 * (line.at(15) - '0') +
							1 * (line.at(16) - '0');

						strPos = 19;
						strLen = 10 * (line.at(17) - '0') + (line.at(18) - '0');
						if (line.size() - strPos + 1 >= strLen)
						{
							str = line.substr(strPos, strLen);

							font.loadFromFile(str);
						}
					}
					break;
				}


			for (auto& line : lines)
			{
				switch (line.at(0))
				{
				case 'S':
				case 's':
					if (lines.size() >= 10)
					{
						x = 10 * (line.at(1) - '0') + (line.at(2) - '0');
						y = 10 * (line.at(3) - '0') + (line.at(4) - '0');
						w = 10 * (line.at(5) - '0') + (line.at(6) - '0');
						h = 10 * (line.at(7) - '0') + (line.at(8) - '0');

						strPos = 11;
						strLen = 10 * (line.at(9) - '0') + (line.at(10) - '0');
						if (line.size() - 10 >= strLen)
							str = line.substr(strPos, strLen);

						addSection(vec2(x, y), vec2(w, h),
							&style, str, &font);
					}
					break;

				case 'B':
				case 'b':
					if (lines.size() >= 10)
					{
						x = 10 * (line.at(1) - '0') + (line.at(2) - '0');
						y = 10 * (line.at(3) - '0') + (line.at(4) - '0');
						w = 10 * (line.at(5) - '0') + (line.at(6) - '0');
						h = 10 * (line.at(7) - '0') + (line.at(8) - '0');

						strPos = 11;
						strLen = 10 * (line.at(9) - '0') + (line.at(10) - '0');
						if (line.size() - strPos + 1 + 2 >= strLen)
						{
							str = line.substr(strPos, strLen);

							strPos += strLen + 2;
							strLen = 10 * (line.at(strPos - 2) - '0') +
								(line.at(strPos - 1) - '0');

							if (line.size() - strPos + 1 >= strLen)
							{
								str2 = line.substr(strPos, strLen);

								sections.back().addButton(vec2(x, y),
									vec2(w, h), &style, str, &font);
							}
						}
					}
					break;

				case 'T':
				case 't':
					if (lines.size() >= 10)
					{
						x = 10 * (line.at(1) - '0') + (line.at(2) - '0');
						y = 10 * (line.at(3) - '0') + (line.at(4) - '0');
						w = 10 * (line.at(5) - '0') + (line.at(6) - '0');
						h = 10 * (line.at(7) - '0') + (line.at(8) - '0');

						strPos = 11;
						strLen = 10 * (line.at(9) - '0') + (line.at(10) - '0');
						if (line.size() - strPos + 1 + 2 >= strLen)
						{
							str = line.substr(strPos, strLen);

							strPos += strLen + 2;
							strLen = 10 * (line.at(strPos - 2) - '0') +
								(line.at(strPos - 1) - '0');

							if (line.size() - strPos + 1 >= strLen)
							{
								str2 = line.substr(strPos, strLen);

								sections.back().addToggle(vec2(x, y),
									vec2(w, h), &style, str, &font);
							}
						}
					}
					break;

				case 'X':
				case 'x':
					if (lines.size() >= 10)
					{
						x = 10 * (line.at(1) - '0') + (line.at(2) - '0');
						y = 10 * (line.at(3) - '0') + (line.at(4) - '0');
						w = 10 * (line.at(5) - '0') + (line.at(6) - '0');
						h = 10 * (line.at(7) - '0') + (line.at(8) - '0');

						strPos = 11;
						strLen = 10 * (line.at(9) - '0') + (line.at(10) - '0');
						if (line.size() - strPos + 1 + 2 >= strLen)
						{
							str = line.substr(strPos, strLen);

							sections.back().addTextbox(vec2(x, y),
								vec2(w, h), &style, str, &font);
						}
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
								clean[clean.size() -1 - strLen] += strLen % 10;
								clean[clean.size() -2 - strLen] += strLen / 10;
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
		Style style;
	};

}