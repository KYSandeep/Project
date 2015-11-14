/*   This a simple version of the arcade game tron
   Copyright (C) 2015  K Y Sandeep

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA

   Gnomovision version 69, Copyright (C) year  name of author
   Gnomovision comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
   This is free software, and you are welcome to redistribute it
   under certain conditions; type `show c' for details

*/
#ifndef ENGINE_DEFINED
#define ENGINE_DEFINED
#define SCREENHEIGHT 24
#define SCREENWIDTH 80
#define MAXSQUARES (SCREENHEIGHT * SCREENWIDTH)

#define WALL 'W'
#define WALLCHAR ' '
#define SNAKEHEAD ' '
#define SNAKEBODY ' '


#define SNAKE1_COLORCODE 1
#define SNAKE2_COLORCODE 2
#define WALL_COLORCODE 3
#define OUTSIDE_COLORCODE 4
#define SNAKE1HEAD_COLORCODE 5
#define SNAKE2HEAD_COLORCODE 6

#define COLOR_GREY 8
struct gamestructure {
	char state;
	char speed;
	int difficulty;
	int depth;
	char winner;

	char map[SCREENWIDTH][SCREENHEIGHT];
};

#define SINGLEPLAYERGAME 1
#define TWOPLAYERGAME 2
#define PAUSED 3
#define MAIN_MENU 4
#define END_MENU 5


#define GAMEDELAY (50000 * (5 - game.speed))
#define MAXKEYBUFFERSIZE 3
#define ENGINETIMEOUTCOUNTER 30

#define PLAYER1 1
#define PLAYER2 2
#define DRAW 0

extern struct gamestructure game;
void engineInit();
void engineDrawWalls();
void engineClearMap();
void engineStartGameEnvironment();
void engineStartMenuEnvironment();
void engineProcessGameWinner();

#define engineAddChar(m_x, m_y, m_char)  mvaddch  (m_y, m_x, m_char)
#define engineAddStr(m_x, m_y, m_str)    mvaddstr (m_y, m_x, m_str)
#define enginePrintF(m_x, m_y, ...)      mvprintw (m_y, m_x, __VA_ARGS__)
#define engineAddCharFromPoint(m_point, m_symbol) mvaddch(m_point.y, m_point.x, m_symbol)

#define MAXQUEUESIZE 10


typedef struct queue_ {
	int* data;
	int maxqueuesize;
	int front;
	int behindback;
	int lastenqueued;
	int size;
} queue;

void InitQueue (queue* q, int* array, int arraysize);
void enqueue (queue* q, int val);
int dequeue (queue* q);
void FreeQueue (queue* q);



#endif
