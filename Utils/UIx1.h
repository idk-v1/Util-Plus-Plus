#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>

namespace UIx1
{
	using vec2f = sf::Vector2f;
	using vec2i = sf::Vector2i;

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
		RoundedRect(vec2f pPos, vec2f pSize, 
			Style* pStylePtr, int pSpaceLvl = 1)
		{
			pos = pPos;
			size = pSize;
			st = pStylePtr;
			spaceLvl = pSpaceLvl;

			int corner = 2 * st->rad - st->space * spaceLvl;

			wRect.setSize(vec2f(
				size.x * st->scale - 2 * st->space * spaceLvl, 
				size.y * st->scale - 2 * st->rad - 2 * st->space));
			wRect.setPosition(
				pos.x * st->scale + st->space * spaceLvl, 
				pos.y * st->scale + st->rad + st->space);

			hRect.setSize(vec2f(
				size.x * st->scale - 2 * st->rad - 2 * st->space, 
				size.y * st->scale - 2 * st->space * spaceLvl));
			hRect.setPosition(
				pos.x * st->scale + st->rad + st->space, 
				pos.y * st->scale + st->space * spaceLvl);

			tlCirc.setRadius(st->rad - st->space * spaceLvl);
			tlCirc.setPosition(
				pos.x * st->scale + st->space * spaceLvl, 
				pos.y * st->scale + st->space * spaceLvl);

			trCirc.setRadius(st->rad - st->space * spaceLvl);
			trCirc.setPosition(
				(pos.x + size.x) * st->scale - corner,
				pos.y * st->scale + st->space * spaceLvl);

			brCirc.setRadius(st->rad - st->space * spaceLvl);
			brCirc.setPosition(
				(pos.x + size.x) * st->scale - corner,
				(pos.y + size.y) * st->scale - corner);

			blCirc.setRadius(st->rad - st->space * spaceLvl);
			blCirc.setPosition(
				pos.x * st->scale + st->space * spaceLvl, 
				(pos.y + size.y) * st->scale - corner);
		}

		sf::IntRect getRect()
		{
			return sf::IntRect(
				vec2i(pos) * st->scale, 
				vec2i(size) * st->scale);
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
		vec2f pos, size;
		int spaceLvl = 1;
	};

	class Input : public sf::Drawable 
	{
	public:
		Input() {}
		Input(vec2f pPos, vec2f pSize, Style* pStylePtr, std::string pLabelStr,
			sf::Font* pFontPtr, int pFontSize, Color pColor)
		{
			pos = pPos;
			size = pSize;
			st = pStylePtr;

			rect = RoundedRect(pos, size, st, 2);

			setColor(pColor);

			text.setFont(*pFontPtr);
			text.setString(pLabelStr);
			text.setCharacterSize(pFontSize);

			vec2i textSize(
				text.getLocalBounds().width, 
				text.getLocalBounds().height);

			text.setPosition(
				(pos.x + size.x / 2.f) * st->scale - 
				(textSize.x + st->space) / 2.f,
				(pos.y + size.y / 2.f) * st->scale - 
				textSize.y / 2.f - st->space);
		}

		virtual void setColor(Color pColor)
		{
			color = pColor;
			rect.setColor(color.back);
			text.setFillColor(color.text);
		}

		virtual void click() {}

		bool hoverCheck(sf::Vector2i pMousePos)
		{
			changed = false;
			return rect.getRect().contains(pMousePos);
		}

		bool hasChanged()
		{
			return changed;
		}

		virtual void hoverColor(bool pHover) {}

	protected:
		Style* st;
		vec2f pos, size;
		RoundedRect rect;
		Color color;
		sf::Text text;
		bool changed = false;

	private:
		virtual void draw(sf::RenderTarget& target, 
			sf::RenderStates states) const {}
	};

	class ExecInput : public Input
	{
	public:
		ExecInput() {}
		ExecInput(vec2f pPos, vec2f pSize, Style* pStylePtr, 
			std::string pLabelStr, sf::Font* pFontPtr, std::string pExec, 
			int pFontSize, Color pColor) : Input(pPos, pSize, pStylePtr, 
				pLabelStr, pFontPtr, pFontSize, pColor)
		{
			exec = pExec;
		}

		virtual void hoverColor(bool pHover)
		{
			setColor(color);
			if (pHover)
				rect.setColor(color.back + hiColor);
		}

		bool startProc(std::string pExec, int pTimeout, std::string pArgs = "")
		{
			unsigned long exit, status;
			STARTUPINFOA info = { sizeof(info) };
			PROCESS_INFORMATION processInfo;

			pArgs.insert(0, " ");

			if (CreateProcessA(pExec.data(), &pArgs[0], NULL, NULL, TRUE, 0, 
				NULL, NULL, &info, &processInfo))
			{
				WaitForSingleObject(processInfo.hProcess, pTimeout);
				status = GetExitCodeProcess(processInfo.hProcess, &exit);
				CloseHandle(processInfo.hProcess);
				CloseHandle(processInfo.hThread);
				return exit;
			}
			return 0;
		}

	protected:
		std::string exec;

		sf::Color hiColor = sf::Color(0x1F1F1FFF);
	};

	class Button : public ExecInput
	{
	public:
		Button() {}
		Button(vec2f pPos, vec2f pSize, Style* pStylePtr, 
			std::string pLabelStr, sf::Font* pFontPtr, std::string pExec,
			int pFontSize, Color pColor) : 
			ExecInput(pPos, pSize, pStylePtr,
				pLabelStr, pFontPtr, pExec, pFontSize, pColor) { }

		void click()
		{
			changed = true;
			startProc(exec, 0);
		}

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(rect, states);
			target.draw(text, states);
		}
	};

	class Toggle : public ExecInput
	{
	public:
		Toggle() {}
		Toggle(vec2f pPos, vec2f pSize, Style* pStylePtr, 
			std::string pLabelStr, sf::Font* pFontPtr, std::string pExec, 
			int pFontSize, Color pColor) : 
			ExecInput(pPos, pSize, pStylePtr, 
				pLabelStr, pFontPtr, pExec, pFontSize, pColor)
		{
			state = startProc(exec, INFINITE);
			rect.setColor(state ? color.front : color.back);
		}

		void click()
		{
			changed = true;
			state = !startProc(exec, INFINITE, "X");

			rect.setColor(state ? color.front : color.back);
		}

		void hoverColor(bool pHover)
		{
			setColor(color);
			if (pHover)
				rect.setColor((state ? color.front : color.back) + hiColor);
		}

		void setColor(Color pColor)
		{
			color = pColor;
			rect.setColor(state ? color.front : color.back);
			text.setFillColor(color.text);
		}

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(rect, states);
			target.draw(text, states);
		}

		bool state = false;
	};

	class Textbox : public Input
	{
	public:
		Textbox() {}
		Textbox(vec2f pPos, vec2f pSize, Style* pStylePtr,
			std::string pLabelStr, sf::Font* pFontPtr, int pFontSize,
			Color pColor) :
			Input(pPos, pSize, pStylePtr, pLabelStr, pFontPtr,
				pFontSize, pColor) {}

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(rect, states);
			target.draw(text, states);
		}
	};

	class Section : public sf::Drawable
	{
	public:
		Section() {}
		Section(vec2f pPos, vec2f pSize, Style* pStylePtr, 
			std::string pLabelStr, sf::Font* pFontPtr, Color* pColorPtr, 
			int pFontSize)
		{
			pos = pPos;
			size = vec2f(pSize.x, pSize.y);
			st = pStylePtr;
			colorPtr = pColorPtr;
			fontPtr = pFontPtr;

			if (!pLabelStr.empty())
			{
				labelStr = pLabelStr;
				label.setFont(*fontPtr);
				label.setCharacterSize(pFontSize);
				label.setString(labelStr);
				label.setPosition(
					pos.x * st->scale + (size.x * st->scale -
						label.getLocalBounds().width) / 2.f,
					pos.y * st->scale + st->space);

				labelRect = RoundedRect(pos, vec2f(size.x, 1), st);
				labelRect.setColor(colorPtr->front);
				label.setFillColor(colorPtr->text);
			}

			bodyRect = RoundedRect(pos, size, st);
			bodyRect.setColor(colorPtr->back);
		}

		void hoverCheck(sf::Vector2i& pMousePos, bool pFocus, bool pClick)
		{
			for (auto& input : inputs)
			{
				if (pFocus && input->hoverCheck(pMousePos))
				{
					input->hoverColor(true);
					if (pClick)
						input->click();
				}
				else
					input->hoverColor(false);
			}
		}

		void addButton(vec2f pPos, vec2f pSize, Style* pStylePtr, 
			std::string str, sf::Font* pFontPtr, std::string pExec, 
			int pFontSize)
		{
			inputs.push_back(new Button(
				vec2f(pPos.x + pos.x, pPos.y + pos.y), pSize, pStylePtr, 
				str, pFontPtr, pExec, pFontSize, *colorPtr));
		}

		void addToggle(vec2f pPos, vec2f pSize, Style* pStylePtr, 
			std::string str, sf::Font* pFontPtr, std::string pExec, 
			int pFontSize)
		{
			inputs.push_back(new Toggle(
				vec2f(pPos.x + pos.x, pPos.y + pos.y), pSize, pStylePtr, 
				str, pFontPtr, pExec, pFontSize, *colorPtr));
		}

		void addTextbox(vec2f pPos, vec2f pSize, Style* pStylePtr, 
			std::string str, sf::Font* pFontPtr, int pFontSize)
		{
			inputs.push_back(new Textbox(
				vec2f(pPos.x + pos.x, pPos.y + pos.y), pSize, pStylePtr, 
				str, pFontPtr, pFontSize, *colorPtr));
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

		Color* colorPtr;

		std::vector<Input*> inputs;

		vec2f pos, size;
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

		bool loadFile(std::string pFileName, sf::Vector2u* winSize)
		{
			std::ifstream file(pFileName);
			std::string data, clean;
			std::vector<std::string> lines;
			bool inQuote = false;

			if (file.is_open())
			{
				while (std::getline(file, data))
				{
					clean.clear();
					for (char c : data)
					{
						if (c == '"')
							inQuote = !inQuote;
						else if (c == '`')
							clean.push_back('\n');
						else if (c != '\t' && (c != ' ' || inQuote))
							clean.push_back(c);
					}
					if (clean.size() && clean.at(0) != '#')
						lines.push_back(clean);
				}
				file.close();
				readLines(lines, winSize);
				return true;
			}
			return false;
		}

		void addSection(vec2f pPos, vec2f pSize, Style* pStylePtr, 
			std::string pString, sf::Font* pFontPtr, int pFontSize)
		{
			sections.push_back(Section(pPos, pSize, pStylePtr, pString, 
				pFontPtr, &color, pFontSize));
		}

		Section* getSectionPtr(size_t pIndex)
		{
			if (pIndex >= 0 && pIndex < sections.size())
				return &sections[pIndex];
			return nullptr;
		}

		size_t numSection()
		{
			return sections.size();
		}

		void update(sf::RenderWindow& pWin)
		{
			bool click = sf::Mouse::isButtonPressed(sf::Mouse::Left);
			sf::Vector2i mousePos = sf::Mouse::getPosition(pWin);
			for (auto& sec : sections)
				sec.hoverCheck(mousePos, pWin.hasFocus(), click && !clickLast);
			clickLast = click;
		}

		Style* getStylePtr()
		{
			return &style;
		}

		sf::Font* getFontPtr()
		{
			return &font;
		}

		void setColor(sf::Color pFront, sf::Color pBack, sf::Color pText)
		{
			color.front = pFront;
			color.back = pBack;
			color.text = pText;
		}

	private:
		size_t findComma(std::string& pStr, size_t pStart)
		{
			bool inQuote = false;
			for (size_t i = pStart; i < pStr.size(); i++)
			{
				if (pStr.at(i) == '"')
					inQuote = !inQuote;
				else if (pStr.at(i) == ',' && !inQuote)
					return i;
			}
			return pStr.size();
		}

		int readInt(std::string& pVal, size_t& pStart)
		{
			int val;
			size_t end = findComma(pVal, ++pStart);

			try
			{
				val = std::stoi(pVal.substr(pStart, end - pStart));
			}
			catch (std::invalid_argument const& ex)
			{
				val = 0;
			}

			pStart = end;
			return val;
		}

		sf::Color readHex(std::string& pVal, size_t& pStart)
		{
			unsigned int val;
			size_t end = findComma(pVal, ++pStart);

			try
			{
				if (end - pStart == 6)
					val = std::stoull(pVal.substr(pStart, end - pStart) + "FF", 
						nullptr, 16);
				else	
					val = std::stoull(pVal.substr(pStart, end - pStart), 
						nullptr, 16);
			}
			catch (std::invalid_argument const& ex)
			{
				val = 0;
			}

			pStart = end;
			return sf::Color(val);
		}

		std::string readStr(std::string pVal, size_t& pStart)
		{
			std::string str;
			size_t end = findComma(pVal, ++pStart);

			str = pVal.substr(pStart, end - pStart);
			pStart = end;

			return str;
		}

		void readLines(std::vector<std::string>& lines, sf::Vector2u* winSize)
		{
			size_t index;

			int numI;
			int num[5];

			int hexI;
			sf::Color hex[3];

			int strI;
			std::string str[2];

			for (auto& line : lines)
				if (line.at(0) == '?')
				{
					numI = hexI = strI = 0;
					index = findComma(line, 0);

					num[numI++] = readInt(line, index);
					num[numI++] = readInt(line, index);
					num[numI++] = readInt(line, index);
					num[numI++] = readInt(line, index);
					num[numI++] = readInt(line, index);
					str[strI++] = readStr(line, index);
					
					winSize->x  = num[0];
					winSize->y  = num[1];
					style.scale = num[2];
					style.rad   = num[3];
					style.space = num[4];
					font.loadFromFile(str[0]);

					winSize->x *= style.scale;
					winSize->y *= style.scale;
					break;
				}

			for (auto& line : lines)
			{
				numI = hexI = strI = 0;
				index = findComma(line, 0);

				switch (line.at(0))
				{
				case 'S':
				case 's': // Section
					num[numI++] = readInt(line, index);
					num[numI++] = readInt(line, index);
					num[numI++] = readInt(line, index);
					num[numI++] = readInt(line, index);
					str[strI++] = readStr(line, index);
					num[numI++] = readInt(line, index);
					
					addSection(vec2f(num[0], num[1]), vec2f(num[2], num[3]), 
						&style, str[0], &font, num[4]);

					break;
				case 'B':
				case 'b': // Button
					num[numI++] = readInt(line, index);
					num[numI++] = readInt(line, index);
					num[numI++] = readInt(line, index);
					num[numI++] = readInt(line, index);
					str[strI++] = readStr(line, index);
					num[numI++] = readInt(line, index);
					str[strI++] = readStr(line, index);
					
					sections.back().addButton(vec2f(num[0], num[1]), 
						vec2f(num[2], num[3]), &style, str[0], &font, str[1], 
						num[4]);
					
					break;
				case 'T':
				case 't': // Toggle
					num[numI++] = readInt(line, index);
					num[numI++] = readInt(line, index);
					num[numI++] = readInt(line, index);
					num[numI++] = readInt(line, index);
					str[strI++] = readStr(line, index);
					num[numI++] = readInt(line, index);
					str[strI++] = readStr(line, index);
					
					sections.back().addToggle(vec2f(num[0], num[1]), 
						vec2f(num[2], num[3]), &style, str[0], &font, str[1], 
						num[4]);
					
					break;
				case 'X':
				case 'x': // Textbox
					num[numI++] = readInt(line, index);
					num[numI++] = readInt(line, index);
					num[numI++] = readInt(line, index);
					num[numI++] = readInt(line, index);
					str[strI++] = readStr(line, index);
					num[numI++] = readInt(line, index);
					
					sections.back().addTextbox(vec2f(num[0], num[1]), 
						vec2f(num[2], num[3]), &style, str[0], &font, num[4]);

					break;
				case 'C':
				case 'c': // Color
					hex[hexI++] = readHex(line, index);
					hex[hexI++] = readHex(line, index);
					hex[hexI++] = readHex(line, index);
					
					color.front = hex[0];
					color.back = hex[1];
					color.text = hex[2];

					break;

				}
			}
		}

		void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			for (auto& section : sections)
				target.draw(section, states);
		}

		std::vector<Section> sections;
		sf::Font font;
		Style style;
		Color color;
		bool clickLast = false;
	};

}