#include "Text.h"

void clearScreen(char fill = ' ') {
	COORD tl = { 0,0 };
	CONSOLE_SCREEN_BUFFER_INFO s;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &s);
	DWORD written, cells = s.dwSize.X * s.dwSize.Y;
	FillConsoleOutputCharacter(console, fill, cells, tl, &written);
	FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
	SetConsoleCursorPosition(console, tl);
}

int main() {
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 1920, 1080, TRUE);

	using enum Baka::BakaColors;

	unsigned int markerPos = 1;
	const char* text;

	Baka::BakaText title(Baka::titleGhost, RED);
	Baka::BakaText menu;

	while (1) {
		clearScreen();
		std::cout << title;
		std::cout << "\n\n\n";
		text = (markerPos == 1) ? ">Start Game" : " StartGame";
		menu.colorMessage(text, RED);
		std::cout << menu << std::endl;
		text = (markerPos == 2) ? ">Settings" : " Settings";
		menu.setMessage(text);
		std::cout << menu << std::endl;
		text = (markerPos == 3) ? ">Exit" : " Exit";
		menu.setMessage(text);
		std::cout << menu << std::endl;

		int c;
		switch (c = _getch()) {
			case 72:
				if (markerPos == 1) {
					break;
				} 

				markerPos -= 1;
				break;
			case 80:
				if (markerPos == 3) {
					break;
				}

				markerPos += 1;
				break;
			case 75:
				break;
			case 77:
				break;
			default:
				break;
		}
	}

	
	
	Baka::BakaText::resetColor();
}