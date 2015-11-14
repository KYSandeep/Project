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

#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <limits.h>

#include "works.h"
#include "bike.h"
#include "ai.h"

pthread_mutex_t processing = PTHREAD_MUTEX_INITIALIZER;
int doneflag;


int directions[] = {LEFT, UP, RIGHT, DOWN};

queue dijk_unvisited_x, dijk_unvisited_y;
int dijk_unvisited_x_arr[MAXSQUARES], dijk_unvisited_y_arr[MAXSQUARES];
int dijk_seq[4] = {0, 0, 1, -1}; 


void *aiProcessGame(void *data){    
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

	struct snakestructure* botsnakepointer = *((struct snakestructure**) data + 0);
	struct snakestructure* usrsnakepointer = *((struct snakestructure**) data + 1);

	botsnakepointer->bot_newdirection = aiMinimax(botsnakepointer, usrsnakepointer);

	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
	pthread_cleanup_push(aiUnlockMutex, (void *) &processing);
	pthread_mutex_lock(&processing);

	doneflag = 1;

	pthread_cleanup_pop(1);
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

	return NULL;
}



void aiUnlockMutex( void *data){
	pthread_mutex_unlock((pthread_mutex_t *)data);
	return;
}


int aiMinimax(struct snakestructure* botsnakepointer, struct snakestructure* usrsnakepointer){
	struct future FG; 
	int i, j;

	memcpy (FG.map, game.map, (SCREENWIDTH * SCREENHEIGHT * sizeof(char)));
	memcpy (&(FG.bot), botsnakepointer, sizeof(struct snakestructure));
	memcpy (&(FG.usr), usrsnakepointer, sizeof(struct snakestructure));

	int alpha = INT_MIN; 

	int beta = INT_MAX;  

	int movesarray[2][3]; 
	j = 0;
	for (i=0; i<4; i++){
		if (snakeIsDirectionAllowed (FG.bot, directions[i])) {
			movesarray[0][j] = directions[i];
			movesarray[1][j] = aiScore(FG, directions[i], 0, alpha, beta);
			if (alpha < movesarray[1][j]) alpha = movesarray[1][j];
			j++;
		}
	}


	return movesarray[0][aiMaxOf3(movesarray[1])];
}




int aiScore( struct future FG, int direction, int depth, int alpha, int beta){
	snakeUpdateDirection (FG.bot, direction);
	aiElongate (FG.bot);

	if (FG.bot.alive == 0) return INT_MIN/3;	

	int i;
	int j = 0;
	int subscores[3];
	for (i=0; i<4; i++){
		if (snakeIsDirectionAllowed (FG.usr, directions[i])) {
			subscores[j] = aiSubScore(FG, directions[i], depth + 1, alpha, beta);
			if (beta > subscores[j]) beta = subscores[j];
			if (alpha > beta) return INT_MIN;
			j++;
		}
	}

	return (subscores[aiMinOf3(subscores)]);
}



int aiSubScore( struct future FG, int direction, int depth, int alpha, int beta){
	snakeUpdateDirection (FG.usr, direction);
	aiElongate (FG.usr);
	if (FG.usr.alive == 0) return INT_MAX/3;

	if (depth >= game.depth) return aiVoronoi(&FG);

	int i;
	int j = 0;
	int scores[3];
	for (i=0; i<4; i++){
		if (snakeIsDirectionAllowed (FG.bot, directions[i])) {
			scores[j] = aiScore(FG, directions[i], depth, alpha, beta);
			if (alpha < scores[j]) alpha = scores[j];
			if (beta < alpha) return INT_MAX;

			j++;
		}
	}

	return scores[aiMaxOf3(scores)];
}



int aiVoronoi(struct future* FGptr){  
	int botcomponent, usrcomponent, result = 0;

	FGptr->map[FGptr->usr.head.x][FGptr->usr.head.y] = FGptr->map[FGptr->bot.head.x][FGptr->bot.head.y] = 0;

	botcomponent = aiDijkstra(FGptr->map, FGptr->botdistancemap, FGptr->bot.head.x, FGptr->bot.head.y);
	usrcomponent = aiDijkstra(FGptr->map, FGptr->usrdistancemap, FGptr->usr.head.x, FGptr->usr.head.y);

	if (FGptr->botdistancemap[FGptr->usr.head.x][FGptr->usr.head.y] == -1) result = (botcomponent - usrcomponent) * 10000;

	int x, y;
	for (y=0; y<SCREENHEIGHT; y++){
		for (x=0; x<SCREENWIDTH; x++){
			if (FGptr->botdistancemap[x][y] == -1) result -= 50;
			if (FGptr->usrdistancemap[x][y] == -1) result += 50;
			if ((FGptr->usrdistancemap[x][y] > 0) && (FGptr->botdistancemap[x][y] > 0)){
				if (FGptr->usrdistancemap[x][y] > FGptr->botdistancemap[x][y]) result += 10;
				if (FGptr->usrdistancemap[x][y] < FGptr->botdistancemap[x][y]) result -= 10;
				result += (FGptr->usrdistancemap[x][y]) / 30;
				result -= (FGptr->botdistancemap[x][y]) / 30;
			}
		}
	}

	return result;
}




int aiDijkstra(char map[SCREENWIDTH][SCREENHEIGHT], int distance[SCREENWIDTH][SCREENHEIGHT], int start_x, int start_y){
	int x, y;
	int i, j, k;
	int componentsize = 0;

	for (x=0; x<SCREENWIDTH; x++){
		for (y=0; y<SCREENHEIGHT; y++){
			distance[x][y] = -1;
		}
	}

	InitQueue (&dijk_unvisited_x, dijk_unvisited_x_arr, MAXSQUARES);
	InitQueue (&dijk_unvisited_y, dijk_unvisited_y_arr, MAXSQUARES);

	enqueue (&dijk_unvisited_x, start_x);
	enqueue (&dijk_unvisited_y, start_y);
	distance[start_x][start_y] = 0;
	char temp = map[start_x][start_y];


	while(dijk_unvisited_x.size > 0){
		x = dequeue (&dijk_unvisited_x);
		y = dequeue (&dijk_unvisited_y);
		componentsize++;


		for (k=0; k < 4; k++){
			i = dijk_seq[k];
			j = dijk_seq[3-k];
			if ((map[x+i][y+j] == 0) && (distance[x+i][y+j] == -1)){
				distance[x+i][y+j] = distance[x][y] + 1;
				enqueue (&dijk_unvisited_x, x+i);
				enqueue (&dijk_unvisited_y, y+j);
			}
		}
	}

	return componentsize;
}
