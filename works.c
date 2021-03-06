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

#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>

#include "bike.h"
#include "works.h"
#include "ai.h"

struct gamestructure game;

void engineSleepAndCallBot(struct snakestructure* botsnakepointer, struct snakestructure* usrsnakepointer, long int usleeptime);


void engineInit(){
	(void) initscr();               //Initializing NCURSES

	int current_height, current_width;
	getmaxyx (stdscr, current_height, current_width);

	start_color();


	if ((current_width < SCREENWIDTH) || (current_height < SCREENHEIGHT) || (SCREENHEIGHT < 24) || (SCREENWIDTH < 80)){
		endwin();
		printf ("Your console screen is smaller than %d x %d\nPlease resize your window and try again\nPlease note, the set SCREENWIDTH and SCREENHEIGHT in engine.h must be greater than 24x80\n", SCREENWIDTH, SCREENHEIGHT);
		exit(0);
	}

	raw();                     
	noecho();                   
	keypad(stdscr, TRUE);        
	curs_set(0);                 
	nodelay(stdscr, TRUE);             
	refresh();                     
}



void engineStartGameEnvironment(){
	nodelay(stdscr, TRUE);
	engineClearMap();
	engineDrawWalls();
	snakeInit();
	game.depth = game.difficulty;
	init_pair(SNAKE1_COLORCODE, COLOR_BLUE, COLOR_BLUE);
	init_pair(SNAKE2_COLORCODE, COLOR_RED, COLOR_RED);
	init_pair(SNAKE1HEAD_COLORCODE, COLOR_BLACK, COLOR_BLACK);
	init_pair(SNAKE2HEAD_COLORCODE, COLOR_BLACK, COLOR_BLACK);
	init_pair(WALL_COLORCODE, COLOR_BLACK, COLOR_BLACK);
	init_pair(OUTSIDE_COLORCODE, COLOR_BLACK, COLOR_WHITE);

	refresh();
	flushinp();

	return;
}

void engineStartMenuEnvironment(){
	nodelay(stdscr, FALSE);

	erase();
	refresh();
	flushinp();

	return;
}



void engineDrawWalls(){
	attrset(COLOR_PAIR(OUTSIDE_COLORCODE));
	erase();
	bkgd(COLOR_PAIR(OUTSIDE_COLORCODE));

	attrset(COLOR_PAIR(WALL_COLORCODE));
	int y;
	for (y=0; y<SCREENHEIGHT; y++){
		engineAddChar (0, y, WALLCHAR);
		game.map[0][y] = WALL;

		engineAddChar (SCREENWIDTH - 1, y, WALLCHAR);
		game.map[SCREENWIDTH-1][y] = WALL;
	}

	int x;
	for (x=0; x<SCREENWIDTH; x++){
		engineAddChar (x, 0, WALLCHAR);
		game.map[x][0] = WALL;

		engineAddChar (x, SCREENHEIGHT - 1, WALLCHAR);
		game.map[x][SCREENHEIGHT-1] = WALL;
	}

	return;
}


void engineClearMap(){
	int i, j;
	for (i=0; i<SCREENWIDTH; i++){
		for (j=0; j<SCREENHEIGHT; j++){
			game.map[i][j] = 0;
		}
	}
}

void engineProcessGameWinner(){
	if ((snake1.head.x == snake2.head.x) && (snake1.head.y == snake2.head.y)) snake1.alive = snake2.alive = 0;

	if (snake1.alive != 0) game.winner = 1;
	else if (snake2.alive != 0) game.winner = 2;
	else game.winner = 0;
}







void engineSleepAndCallBot(struct snakestructure* botsnakepointer, struct snakestructure* usrsnakepointer, long int usleeptime){
	struct timespec timeout;
	pthread_t aithread;
	int error = 0;
	void *exitstatus;
	static int counter;
	botsnakepointer->bot_newdirection = botsnakepointer->direction;
	struct snakestructure* snakes[] = {botsnakepointer, usrsnakepointer};
	doneflag = 0;
	pthread_create(&aithread, NULL, aiProcessGame, snakes);
	usleep(usleeptime);
	error = pthread_cancel(aithread);    
	error = pthread_join(aithread, &exitstatus);
	if (doneflag == 1) {
		if (counter > 0) counter--;
		else if (game.depth < game.difficulty) game.depth++;
	}
	if (doneflag == 0) {
		counter = ENGINETIMEOUTCOUNTER;
		game.depth--;
	}

	return;
}

void InitQueue (queue* q, int* array, int arraysize){
	q->size = q->front = q->behindback = 0;
	q->maxqueuesize = arraysize;
	if (array != NULL){
		q->data = array;
	}
	else{
		q->data = (int*) malloc ((q->maxqueuesize + 1) * sizeof(int));
	}
}

void enqueue (queue* q, int val){
	if ((q->size == 0) || (q->behindback != q->front)){
		q->size++;
		q->data[q->behindback] = val;
		q->lastenqueued = val;
		q->behindback = (q->behindback + 1) % q->maxqueuesize;
	}
}

int dequeue (queue* q){
	if (q->size > 0){
		q->size--;
		int returnvalue = q->data[q->front];
		q->front = (q->front + 1) % q->maxqueuesize;
		return returnvalue;
	}
	else return 0;
}


void FreeQueue (queue* q){
	free(q->data);
}
