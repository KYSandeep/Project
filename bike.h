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

#ifndef SNAKE_DEFINED
#define SNAKE_DEFINED

#include "works.h"

#define UP -2
#define DOWN 2
#define LEFT -1
#define RIGHT 1

#define SNAKE1_STARTX 4
#define SNAKE2_STARTX (SCREENWIDTH - 5)
#define SNAKE1_STARTY (SCREENHEIGHT/2)
#define SNAKE2_STARTY (SCREENHEIGHT/2)
#define SNAKE1_STARTDIRECTION RIGHT
#define SNAKE2_STARTDIRECTION LEFT
#define SNAKE1_MARKER 1
#define SNAKE2_MARKER 2

#define MAXSNAKESIZE (MAXSQUARES / 2)

struct point {
	int x;
	int y;
};

#define SetPoint(m_point, m_x, m_y) m_point.x = m_x; m_point.y = m_y
#define MovePoint(m_point, m_x, m_y) m_point.x += m_x; m_point.y += m_y
#define EquatePoint(m_point1, m_point2) m_point1.x = m_point2.x; m_point1.y = m_point2.y

struct snakestructure {
	char alive;

	struct point head;

	int direction;
	int size;

	char marker;
	char colorcode;
	char headcolorcode;

	int bot_newdirection;
};


extern struct snakestructure snake1;
extern struct snakestructure snake2;
void snakeInit();

#define snakeIsDirectionAllowed(macro_snake, macro_direction) (macro_snake.direction + macro_direction != 0)
#define snakeUpdateDirection(macro_snake, macro_direction)  if (macro_snake.direction + macro_direction != 0) {macro_snake.direction = macro_direction;}
#define snakeElongate(m_snake) {                                                            \
	attrset(COLOR_PAIR(m_snake.colorcode));                                 \
	engineAddCharFromPoint (m_snake.head, SNAKEBODY);                       \
	MovePoint (m_snake.head, m_snake.direction % 2, m_snake.direction / 2); \
	\
	if (game.map[m_snake.head.x][m_snake.head.y] != 0) {                    \
		m_snake.alive = 0;                                                  \
	}                                                                   \
	\
	game.map[m_snake.head.x][m_snake.head.y] = m_snake.marker;             \
	attrset(COLOR_PAIR(m_snake.headcolorcode));                             \
	engineAddCharFromPoint (m_snake.head, SNAKEHEAD);                       \
	m_snake.size++;                                                         \
	\
}


#endif        
