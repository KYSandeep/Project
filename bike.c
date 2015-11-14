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

   
*/

#include "bike.h"
#include "works.h"
#include "curses.h"

struct snakestructure snake1;
struct snakestructure snake2;


void snakeInit(){
	snake1.size = snake1.alive = snake2.size = snake2.alive = 1;

	SetPoint (snake1.head, SNAKE1_STARTX, SNAKE1_STARTY);
	SetPoint (snake2.head, SNAKE2_STARTX, SNAKE2_STARTY);

	snake1.marker = SNAKE1_MARKER;
	snake2.marker = SNAKE2_MARKER;

	snake1.colorcode = SNAKE1_COLORCODE;
	snake2.colorcode = SNAKE2_COLORCODE;
	snake1.headcolorcode = SNAKE1HEAD_COLORCODE;
	snake2.headcolorcode = SNAKE2HEAD_COLORCODE;

	game.map[snake1.head.x][snake1.head.y] = snake1.marker;
	game.map[snake2.head.x][snake2.head.y] = snake2.marker;

	snake1.direction = snake1.bot_newdirection = SNAKE1_STARTDIRECTION;
	snake2.direction = snake2.bot_newdirection = SNAKE2_STARTDIRECTION;

	engineAddCharFromPoint (snake1.head, SNAKEHEAD);
	engineAddCharFromPoint (snake2.head, SNAKEHEAD);
}
