//1: Blue
//2 : Green
//3 : Cyan
//4 : Red
//5 : Purple
//6 : Yellow(Dark)
//7 : Default white
//8 : Gray / Grey
//9 : Bright blue
//10 : Brigth green
//11 : Bright cyan
//12 : Bright red
//13 : Pink / Magenta
//14 : Yellow
//15 : Bright white

#include "precum.h"

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

	private:
		const char* m_message;
		BakaColors m_color;
	};
}