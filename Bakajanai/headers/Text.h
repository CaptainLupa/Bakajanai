#pragma once

#ifndef TEXT_H
#define TEXT_H



#include "precomp.h"

namespace Baka {
	enum class BakaColors {
		BLUE = 1,
		GREEN,
		CYAN,
		RED,
		PURPLE,
		DARK_YELLOW,
		WHITE,
		GRAY,
		BRIGHT_BLUE,
		BRIGHT_GREEN,
		BRIGHT_CYAN,
		BRIGHT_RED,
		PINK,
		YELLOW,
		BRIGHT_WHITE
	};

	class BakaText {
	public:
		using enum BakaColors;

		BakaText(): m_message(""), m_color(WHITE) { }

		BakaText(const char* message, BakaColors color): m_message(message), m_color(color) { }
		BakaText(const std::string& message, BakaColors color) : m_message(message), m_color(color) {}
		BakaText(float message, BakaColors color): m_color(color) {
			m_message = std::to_string(message);
		}

		void setColor(BakaColors color = WHITE) {
			m_color = color;
		}

		void setMessage(const char* message) { m_message = message; }

		void colorMessage(const char* message, BakaColors color = WHITE) {
			m_color = color;
			m_message = message;
		}

		static void resetColor() {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}

		friend std::ostream& operator<< (std::ostream& os, const BakaText& bt) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)bt.m_color);
			os << bt.m_message;
			return os;
		}

		static void clearScreen(char fill = ' ') {
			COORD tl = { 0,0 };
			CONSOLE_SCREEN_BUFFER_INFO s;
			HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
			GetConsoleScreenBufferInfo(console, &s);
			DWORD written, cells = s.dwSize.X * s.dwSize.Y;
			FillConsoleOutputCharacter(console, fill, cells, tl, &written);
			FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
			SetConsoleCursorPosition(console, tl);
		}

		static void resizeScreen(int W = 1920, int H = 1080) {
			HWND console = GetConsoleWindow();
			RECT r;
			GetWindowRect(console, &r);
			MoveWindow(console, r.left, r.top, W, H, TRUE);
		}

	private:
		std::string m_message;
		BakaColors m_color;
	};
}

#endif