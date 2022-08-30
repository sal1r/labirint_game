#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#define WIDTH 80
#define HEIGHT 20

typedef struct pos
{
	char x;
	char y;
} pos;

int main(void)
{
	char filename[51];
	printf("%s", "enter file name(max 50 chars): ");
	scanf("%50s", filename);
	initscr();
	refresh();
	noecho();
	int ch = 0;
	curs_set(0);
	pos player = {1, 1};
	pos player_copy = player;
	short blocks_count = 0;
	pos* blocks = NULL;
	FILE* save = fopen(filename, "a+");
	while(fscanf(save, "%u:%u", &player.x, &player.y) != EOF)
	{
			blocks_count++;
			blocks = realloc(blocks, sizeof(pos) * blocks_count);
			blocks[blocks_count - 1].x = player.x;
			blocks[blocks_count - 1].y = player.y;
	}
	fclose(save);
	WINDOW* win = newwin(HEIGHT, WIDTH, 0, 0);
	keypad(stdscr, TRUE);
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_GREEN);
	init_pair(2, COLOR_BLACK, COLOR_WHITE);
	init_pair(3, COLOR_WHITE, COLOR_RED);
	while(1)
	{
		wmove(win, 0, 0);
		for(short i = 0; i < WIDTH * HEIGHT; i++)
			waddch(win, ' ' | COLOR_PAIR(1));
		if(player.x < 0 || player.y < 0 || player.x > WIDTH - 1 || player.y > HEIGHT - 1)
			player = player_copy;
		for(short i = 0; i < blocks_count; i++)
		{
			wmove(win, blocks[i].y, blocks[i].x);
			waddch(win, '#' | COLOR_PAIR(3));
			if(player.x == blocks[i].x && player.y == blocks[i].y)
				player = player_copy;
		}
		wmove(win, player.y, player.x);
		waddch(win, '@' | COLOR_PAIR(2));
		wrefresh(win);
		player_copy = player;
		ch = getch();
		switch (ch)
		{
		case 'W':
		case 'w':
			player.y -= 1;
			break;
		case 'A':
		case 'a':
			player.x -= 1;
			break;
		case 'S':
		case 's':
			player.y += 1;
			break;
		case 'D':
		case 'd':
			player.x += 1;
			break;
		}
	}
	getch();
	endwin();
	return 0;
}