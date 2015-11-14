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
#include "menu.h"
#include "works.h"
#include "tron.h"

enum Colors { BLACK_WHITE = 1, CYAN_BLACK, BLUE_BLACK,
	WHITE_BLACK, GREEN_BLACK, RED_BLACK  , YELLOW_BLACK, BORDER};

int gamemode;
void menuMainMenu(){
	int current_speed = 3;
	int current_difficulty = 2;
	char *difficulty_options[4] = { "EASY", "MEDIUM", "HARD", "BRUTAL"};
	int difficultyoptionsarray[] = {1, 2, 3, 7};
	int speed_options[4] = { 1, 2, 3 ,4};

	int option_row_pos = MENUTEXTSTARTX + 17;

	gamemode = SINGLEPLAYERGAME;

	int wait;
	int i;
	int j;

	while(1){
		wait = TRUE;
		clear ();
		game.state = MAIN_MENU;
		if (has_colors () == TRUE)
		{
			int bg_color;

			start_color ();
			bg_color = COLOR_BLACK;
			init_pair (GREEN_BLACK, COLOR_GREEN, bg_color);
			init_pair (CYAN_BLACK,  COLOR_CYAN,  bg_color);
			init_pair (WHITE_BLACK, COLOR_WHITE, bg_color);
			init_pair (RED_BLACK,   COLOR_RED,   bg_color);
			init_pair (BLUE_BLACK,  COLOR_BLUE,  bg_color);
			init_pair (BLACK_WHITE, COLOR_BLACK, COLOR_WHITE);
			init_pair (YELLOW_BLACK,  COLOR_YELLOW,  bg_color);
			init_pair (BORDER,  COLOR_WHITE,  COLOR_BLUE);
		}

		while (wait == TRUE)
		{
			erase();
			attrset(COLOR_PAIR(CYAN_BLACK)); attron( A_BOLD);
			engineAddStr( LOGOSTARTX, LOGOSTARTY + 0, "88888888 IIIIIII 8888888o.      .o8888o,     888 N      |8 8  ");
			engineAddStr( LOGOSTARTX, LOGOSTARTY + 1, "      88 I             `88.   .88'     88 .  888o N     |8 8  ");
			engineAddStr( LOGOSTARTX, LOGOSTARTY + 2, "      88 I              `88  88'       88 8, 888'o N    |8 8  "); 
			engineAddStr( LOGOSTARTX, LOGOSTARTY + 3, "      88 I              ,88 88'        88 88 888'Yo N   |8 8 " ); 
			engineAddStr( LOGOSTARTX, LOGOSTARTY + 4, "      88 I         .   ,88' 88         88 88 888 'Yo N  |8 8 " ); 
			engineAddStr( LOGOSTARTX, LOGOSTARTY + 5, "      88 I       8888888P'  88         88 88 888  'Yo N |8 8 " );
			attrset(COLOR_PAIR(RED_BLACK)); attron( A_BOLD);
		    	engineAddStr( LOGOSTARTX, LOGOSTARTY + 6, "=================================================================> " ); 
			attrset(COLOR_PAIR(CYAN_BLACK)); attron( A_BOLD);
			engineAddStr( LOGOSTARTX, LOGOSTARTY + 7, "      88 I       88`8b      88,        88 88 888    'Yo V8 8  " ); 
			engineAddStr( LOGOSTARTX, LOGOSTARTY + 8, "      88 I       88 `8b.     88,       88 8' 888     'Yo N 8 " ); 
			engineAddStr( LOGOSTARTX, LOGOSTARTY + 9, "      88 I       88   `8b.    '88,     88 '  888     'Yo N 8   "  ); 
			engineAddStr( LOGOSTARTX, LOGOSTARTY + 10,"      88 I       88     `88.    'D88888'     888      'Yo N8 "  ); 
			attrset(COLOR_PAIR(BLUE_BLACK)); attron( A_BOLD);
		    	engineAddStr( LOGOSTARTX, LOGOSTARTY + 11, "<================================================================  " );

			int i, j;
			for (i=SCREENHEIGHT - 6; i<SCREENHEIGHT-1; i++){
				for (j=0; j<SCREENWIDTH; j++){
					attrset(COLOR_PAIR(BLACK_WHITE));
					engineAddChar( j, i, ' ');
				}
			}

			attrset(COLOR_PAIR(BORDER));
			int y;
			for (y=0; y<SCREENHEIGHT; y++){
				engineAddChar (0, y, ' ');

				engineAddChar (SCREENWIDTH - 1, y, ' ');
			}

			int x;
			for (x=0; x<SCREENWIDTH; x++){
				engineAddChar (x, 0, ' ');

				engineAddChar (x, SCREENHEIGHT - 1, ' ');
			}

			attron( A_DIM);
			enginePrintF(SCREENWIDTH - 51, SCREENHEIGHT - 1, "Space/Enter: Start Game      P: Pause      Q: Quit");

			attrset(COLOR_PAIR(YELLOW_BLACK));
			attron( A_BOLD);
			engineAddStr(GAMEMODESTARTX, GAMEMODESTARTY, "GAME MODE:");
			if (gamemode == SINGLEPLAYERGAME)
			{
				attrset (COLOR_PAIR (WHITE_BLACK));attron( A_BOLD);
				engineAddStr(GAMEMODESTARTX, GAMEMODESTARTY+1, "One Player");

				attrset(COLOR_PAIR(YELLOW_BLACK));
				engineAddStr(GAMEMODESTARTX, GAMEMODESTARTY+2, "Two Players");
			}
			else
			{
				attrset(COLOR_PAIR(YELLOW_BLACK));
				engineAddStr(GAMEMODESTARTX, GAMEMODESTARTY+1, "One Player");

				attrset (COLOR_PAIR (WHITE_BLACK));attron( A_BOLD);
				engineAddStr(GAMEMODESTARTX, GAMEMODESTARTY+2, "Two Players");
			}

			attrset(COLOR_PAIR(RED_BLACK)); attron( A_BOLD);
			engineAddStr(MENUTEXTSTARTX, MENUTEXTSTARTY, "GAME SETTINGS:");
			attrset(COLOR_PAIR(GREEN_BLACK));

			if (gamemode == SINGLEPLAYERGAME){
				attron( A_BOLD);
				engineAddStr(MENUTEXTSTARTX, MENUTEXTSTARTY+2, "Difficulty:");

				for (i = 0, j = 0; i < 4; i++)
				{
					if (i == (current_difficulty-1))
					{attrset (COLOR_PAIR (WHITE_BLACK));attron( A_BOLD);}
					else
						attrset(COLOR_PAIR(GREEN_BLACK));

					mvprintw(MENUTEXTSTARTY + 2, option_row_pos+j, "%s", difficulty_options[i]);	
					if (i == 1)
						j += 9;
					else
						j += 7;
				}
			}
			else{
				attrset(COLOR_PAIR(GREEN_BLACK));
				engineAddStr(MENUTEXTSTARTX, MENUTEXTSTARTY+2, "Blue: W-S-A-D     Red: Up-Down-Left-Right");
			}

			attrset (COLOR_PAIR (CYAN_BLACK));
			attron( A_BOLD);
			engineAddStr(MENUTEXTSTARTX, MENUTEXTSTARTY+1, "Speed:");
			for (i = 0, j = 0; i < 4; i++)
			{
				if (i == (current_speed-1))
				{attrset (COLOR_PAIR (WHITE_BLACK));attron( A_BOLD);}
				else
					attrset (COLOR_PAIR (CYAN_BLACK));

				mvprintw(MENUTEXTSTARTY+1, option_row_pos+j, "%d", speed_options[i]);	
				if (i == 1)
					j += 9;
				else
					j += 7;
			}


			wait = menuGetInput(&current_speed,&current_difficulty);
			refresh ();
		}

		game.speed = current_speed;
		game.difficulty = difficultyoptionsarray[current_difficulty - 1];
		game.state = gamemode;
		standend();
		while (game.state == SINGLEPLAYERGAME)    SinglePlayerGame();
		while (game.state == TWOPLAYERGAME)     TwoPlayerGame();
	}
}


int menuGetInput(int* speed_cur_option, int* diff_cur_option)
{
	nodelay (stdscr, FALSE);

	int input = getch();
	switch (input)
	{
		case 10:	case ' ':
			return FALSE;
			break;

		case 'q':	case 'Q':
			ExitGame();
			break;

		case KEY_UP: 
			gamemode = SINGLEPLAYERGAME;
			break;

		case KEY_DOWN:
			gamemode = TWOPLAYERGAME;
			break;

		case KEY_LEFT:
			if (*diff_cur_option > 1)
				(*diff_cur_option)--;
			break;

		case KEY_RIGHT:
			if (*diff_cur_option < 4)
				(*diff_cur_option)++;
			break;

		case '1': case '2': case '3': case '4':
			*speed_cur_option = (input - '0');
			break;

		default:
			break;
	}

	return TRUE;
}



void menuEndGame()
{	
	int highlight = 1;
	int choice = 0;
	int c;

	engineStartMenuEnvironment();	

	menuEndPrint(highlight);
	while(1)
	{	
		refresh();
		c = getch();

		switch(c)
		{	
			case KEY_UP:
				if(highlight == QUITTOMENU)
					highlight = RESTART;
				break;
			case KEY_DOWN:
				if(highlight == RESTART)
					highlight = QUITTOMENU;
				break;
			case 10:    case ' ':
				choice = highlight;
				break;
			case 'q':	case 'Q':
				ExitGame();
				break;
		}
		menuEndPrint(highlight);
		if(choice == RESTART){
			standend();
			break;
		}
		else if(choice == QUITTOMENU){
			game.state = MAIN_MENU;
			standend();
			break;
		}
	}	

	refresh();
	return;
}

void menuEndPrint(int highlight)
{
	int x, y, i;
	char *choices[] = { 
		"PLAY AGAIN.!",
		"BACK TO MENU",
	};
	int size_choices[] = { 12, 12};

	engineAddStr( ENDBOXSTARTX, ENDBOXSTARTY," ____________________________ ");
	for ( i=1; i<= ENDBOXHEIGHT ; i++){
		engineAddChar( ENDBOXSTARTX, ENDBOXSTARTY + i,'|');
		engineAddChar( ENDBOXENDX, ENDBOXSTARTY + i,'|');
	}
	engineAddStr(ENDBOXSTARTX, ENDBOXENDY, "|____________________________|");

	for(i = 0; i < ENDCHOICES; ++i)
	{	
		x=(( ENDBOXWIDTH - size_choices[i])/2 + ENDBOXSTARTX);
		y= ENDBOXSTARTY+(ENDBOXHEIGHT-ENDCHOICES)/2 +i;
		if(highlight == i + 1)
		{	attron( A_STANDOUT); attron( A_BOLD);
			enginePrintF( x, y, "%s", choices[i]);
			attroff( A_STANDOUT);
		}
		else{
			attron( A_BOLD);
			enginePrintF( x, y, "%s", choices[i]);
		}
	}
	attron( A_BOLD);
	if (game.winner == 1 ){
		if (game.state == TWOPLAYERGAME) enginePrintF( (ENDBOXWIDTH - 18)/2 + ENDBOXSTARTX, ENDBOXENDY-1,"BLUE SNAKE WINS!!!");
		else if (game.state == SINGLEPLAYERGAME) enginePrintF( (ENDBOXWIDTH - 10)/2 + ENDBOXSTARTX, ENDBOXENDY-1,"YOU WON!!!");
	}
	else if (game.winner == 2 ){

		if (game.state == TWOPLAYERGAME) enginePrintF( (ENDBOXWIDTH - 17)/2 + ENDBOXSTARTX, ENDBOXENDY-1,"RED SNAKE WINS!!!");
		else if (game.state == SINGLEPLAYERGAME) enginePrintF( (ENDBOXWIDTH - 11)/2 + ENDBOXSTARTX, ENDBOXENDY-1,"YOU LOST :D");
	}
	else
		enginePrintF( (ENDBOXWIDTH - 9)/2 + ENDBOXSTARTX, ENDBOXENDY-1,"DRAW GAME");
	attroff( A_BOLD);
	refresh();
}


void menuPrintWinner(){
	init_pair (RED_BLACK,   COLOR_RED,   COLOR_BLACK);
	init_pair (BLUE_BLACK,  COLOR_BLUE,  COLOR_BLACK);
	if (game.winner == 1 ){
		attrset(COLOR_PAIR(BLUE_BLACK)); attron( A_BOLD);
		if (game.state == TWOPLAYERGAME) enginePrintF( (ENDBOXWIDTH - 18)/2 + ENDBOXSTARTX, ENDBOXENDY-1,"BLUE SNAKE WINS!!!");
		else if (game.state == SINGLEPLAYERGAME) enginePrintF( (ENDBOXWIDTH - 10)/2 + ENDBOXSTARTX, ENDBOXENDY-1,"YOU WON!!!");
	}
	else if (game.winner == 2 ){
		attrset(COLOR_PAIR(RED_BLACK)); attron( A_BOLD);
		if (game.state == TWOPLAYERGAME) enginePrintF( (ENDBOXWIDTH - 17)/2 + ENDBOXSTARTX, ENDBOXENDY-1,"RED SNAKE WINS!!!");
		else if (game.state == SINGLEPLAYERGAME) enginePrintF( (ENDBOXWIDTH - 11)/2 + ENDBOXSTARTX, ENDBOXENDY-1,"YOU LOST :D");
	}
	refresh();
}

void menuPauseGame(){
	nodelay(stdscr, FALSE);
	getch();
	nodelay(stdscr, TRUE);
}
