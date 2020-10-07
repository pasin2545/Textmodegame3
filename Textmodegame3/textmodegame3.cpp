#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.h>

void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void draw_ship(int x, int y)
{
	gotoxy(x, y); printf(" <-0-> ");
}
void draw_bullet(int x, int y)
{
	gotoxy(x, y); printf("^");
}
void clear_bullet(int x, int y)
{
	gotoxy(x, y); printf(" ");
}
void draw_star(int x, int y) {
	gotoxy(x, y); printf("*");
}
int Score(int x) {
	gotoxy(70, 0);
	return x;
}
char cursor(int x, int y) {
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (
		!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))

		return '\0';
	else
		return buf[0];

}
int main()
{
	srand(time(NULL));
	setcursor(0);
	int n, m;
	int random1[20], random2[20];
	char ch = '.';
	int x = 38, y = 20;
	int bx, by, i = 0, j = 0, score = 0;
	int bullet = 0;
	draw_ship(x, y);
	do {
		if (i < 20 && j < 20) {
			m = 0;
			m = (int)rand() % 6;
			random1[j] = m;
			if (random1[j] < 2) {
				do {
					m = (int)rand() % 5;
					random1[j] = m;
				} while (random1[j] < 2);
			}
			n = 0;
			n = (int)rand() % 71;
			random2[j] = n;
			if (random2[j] < 10) {
				do {
					n = (int)rand() % 71;
					random2[j] = n;
				} while (random2[j] < 10);
			}
			j++;
			//«éÓ
			do {
				if (cursor(random2[i], random1[i]) == '*') {
					m = 0;
					m = (int)rand() % 6;
					random1[i] = m;
					if (random1[i] < 2) {
						do {
							m = (int)rand() % 5;
							random1[i] = m;
						} while (random1[i] < 2);
					}
					n = 0;
					n = (int)rand() % 71;
					random2[i] = n;
					if (random2[i] < 10) {
						do {
							n = (int)rand() % 71;
							random2[i] = n;
						} while (random2[i] < 10);
					}
				}
			} while (cursor(random2[i], random1[i]) == '*');
			draw_star(random2[i], random1[i]);
			i++;
		}
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a') { draw_ship(--x, y); }
			if (ch == 's') { draw_ship(++x, y); }
			if (bullet != 1 && ch == ' ') { bullet = 1; bx = x + 3; by = y - 1; }
			fflush(stdin);
		}
		if (bullet == 1) {

			clear_bullet(bx, by);
			if (by == 2) { bullet = 0; }
			else {
				draw_bullet(bx, --by);
				if (cursor(bx, by - 1) == '*') {
					Beep(3000, 250);
					score += 100;
					gotoxy(bx, by - 1);
					printf(" ");
					bullet = 0;
					clear_bullet(bx, by);
				}
			}
		}
		for (int r = 0; r < 20; r++) {
			do {
				if (cursor(random2[r], random1[r]) == ' ') {
					m = 0;
					m = (int)rand() % 6;
					random1[r] = m;
					if (random1[r] < 2) {
						do {
							m = (int)rand() % 5;
							random1[r] = m;
						} while (random1[r] < 2);
					}
					n = 0;
					n = (int)rand() % 71;
					random2[r] = n;
					if (random2[r] < 10) {
						do {
							n = (int)rand() % 71;
							random2[r] = n;
						} while (random2[r] < 10);
					}
					draw_star(random2[r], random1[r]);
				}
			} while (cursor(random2[r], random1[r]) == ' ');
		}
		Score(score);
		printf("%d", score);
		Sleep(100);
	} while (ch != 'x');
	return 0;
}