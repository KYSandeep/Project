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
#include <unistd.h>
#include <stdlib.h>

#include "works.h"
#include "bike.h"
#include "menu.h"
#include "ai.h"
void engineSleepAndCallBot(struct snakestructure* botsnakepointer, struct snakestructure* usrsnakepointer, long int usleeptime);

void ExitGame(){
	endwin();
	exit(0);
}



void TwoPlayerGame(){
	engineStartGameEnvironment();
	game.state = TWOPLAYERGAME;

	int c, new_direction;

	queue player1buffer, player2buffer;
	int buffer1[MAXKEYBUFFERSIZE], buffer2[MAXKEYBUFFERSIZE];
	InitQueue(&player1buffer, buffer1, MAXKEYBUFFERSIZE);
	InitQueue(&player2buffer, buffer2, MAXKEYBUFFERSIZE);

	player1buffer.lastenqueued = SNAKE1_STARTDIRECTION;
	player2buffer.lastenqueued = SNAKE2_STARTDIRECTION;

	while((snake1.alive == 1) && (snake2.alive == 1)){
		usleep (GAMEDELAY);
		while ((c = getch()) != ERR){
			switch (c){
				case KEY_UP:
					if (player2buffer.lastenqueued != UP) enqueue (&player2buffer, UP);
					break;

				case KEY_LEFT:
					if (player2buffer.lastenqueued != LEFT) enqueue (&player2buffer, LEFT);
					break;

				case KEY_DOWN:
					if (player2buffer.lastenqueued != DOWN) enqueue (&player2buffer, DOWN);
					break;

				case KEY_RIGHT:
					if (player2buffer.lastenqueued != RIGHT) enqueue (&player2buffer, RIGHT);
					break;

				case 'w': case 'W':
					if (player1buffer.lastenqueued != UP) enqueue (&player1buffer, UP);
					break;

				case 'a': case 'A':
					if (player1buffer.lastenqueued != LEFT) enqueue (&player1buffer, LEFT);
					break;

				case 's': case 'S':
					if (player1buffer.lastenqueued != DOWN) enqueue (&player1buffer, DOWN);
					break;

				case 'd': case 'D':
					if (player1buffer.lastenqueued != RIGHT) enqueue (&player1buffer, RIGHT);
					break;

				case 'q':	case 'Q':
					ExitGame();
					break;

				case 'p':	case 'P':
					menuPauseGame();
					break;

				default:
					break;
			}
		}

		if (player1buffer.size != 0) {
			new_direction = dequeue(&player1buffer);
			snakeUpdateDirection(snake1, new_direction);
		}
		if (player2buffer.size != 0) {
			new_direction = dequeue(&player2buffer);
			snakeUpdateDirection(snake2, new_direction);
		}

		snakeElongate (snake1);
		snakeElongate (snake2);
		refresh();
	}

	engineProcessGameWinner();
	menuPrintWinner();
	usleep(3000000);
	menuEndGame();
	return;
}



void SinglePlayerGame(){

	engineStartGameEnvironment();
	game.state = SINGLEPLAYERGAME;

	int c, new_direction;

	queue player1buffer;
	int buffer1[MAXKEYBUFFERSIZE];
	InitQueue(&player1buffer, buffer1, MAXKEYBUFFERSIZE);
	player1buffer.lastenqueued = SNAKE1_STARTDIRECTION;

	while((snake1.alive == 1) && (snake2.alive == 1)){
		engineSleepAndCallBot(&snake2, &snake1, GAMEDELAY);
		while ((c = getch()) != ERR){
			switch (c){
				case ERR:
					break;

				case KEY_UP:
					if (player1buffer.lastenqueued != UP) enqueue (&player1buffer, UP);
					break;

				case KEY_LEFT:
					if (player1buffer.lastenqueued != LEFT) enqueue (&player1buffer, LEFT);
					break;

				case KEY_DOWN:
					if (player1buffer.lastenqueued != DOWN) enqueue (&player1buffer, DOWN);
					break;

				case KEY_RIGHT:
					if (player1buffer.lastenqueued != RIGHT) enqueue (&player1buffer, RIGHT);
					break;

				case 'q':	case 'Q':
					ExitGame();
					break;

				case 'p':	case 'P':
					menuPauseGame();
					break;

				default:
					break;
			}
		}

		snakeUpdateDirection(snake2, snake2.bot_newdirection);

		if (player1buffer.size != 0) {
			new_direction = dequeue(&player1buffer);
			snakeUpdateDirection(snake1, new_direction);
		}

		snakeElongate (snake2);
		snakeElongate (snake1);

		refresh();
	}
	engineProcessGameWinner();
	menuPrintWinner();

	usleep(3000000);
	menuEndGame();
	return;

}


int main(){
	engineInit();
	menuMainMenu();
	ExitGame();
}

