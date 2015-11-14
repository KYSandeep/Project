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
#ifndef AI_DEFINED
#define AI_DEFINED


#define LEFTTURN -1
#define STRAIGHT 0
#define RIGHTTURN 1
#define FG futuregame


extern int doneflag;


#include "works.h"
#include "bike.h"

struct future{
	char map[SCREENWIDTH][SCREENHEIGHT];
	struct snakestructure bot;
	struct snakestructure usr;

	int botdistancemap[SCREENWIDTH][SCREENHEIGHT];
	int usrdistancemap[SCREENWIDTH][SCREENHEIGHT];
};


void* aiProcessGame(void *data);
int aiMinimax(struct snakestructure* botsnakepointer, struct snakestructure* usrsnakepointer);
int aiMaxOf3( int *);
int aiScore( struct future futuregame, int direction, int depth, int alpha, int beta);
int aiSubScore( struct future futuregame, int direction, int depth, int alpha, int beta);

int aiDijkstra(char map[SCREENWIDTH][SCREENHEIGHT], int distance[SCREENWIDTH][SCREENHEIGHT], int start_x, int start_y);
int aiVoronoi(struct future* FGptr);

void aiUnlockMutex(void*);


#define aiMaxOf3(m_arr) ( m_arr[2]>m_arr[((m_arr[1]>m_arr[0])?1:0)])?2:((m_arr[1]>m_arr[0])?1:0)

#define aiMinOf3(m_arr) ( m_arr[2]<m_arr[((m_arr[1]<m_arr[0])?1:0)])?2:((m_arr[1]<m_arr[0])?1:0)


#define aiElongate(m_snake) {                                                            \
	MovePoint (m_snake.head, m_snake.direction % 2, m_snake.direction / 2); \
	\
	if (FG.map[m_snake.head.x][m_snake.head.y] != 0) {                    \
		m_snake.alive = 0;                                                  \
	}                                                                   \
	\
	FG.map[m_snake.head.x][m_snake.head.y] = m_snake.marker;             \
	m_snake.size++;                                                         \
	\
}


#endif
