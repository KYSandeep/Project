#include<stdio.h>
#include <curses.h>
#include "menu.h"
#include "works.h"
#include "tron.h"


enum Colors { BLACK_WHITE = 1, CYAN_BLACK, BLUE_BLACK,
              WHITE_BLACK, GREEN_BLACK, RED_BLACK  , YELLOW_BLACK, BORDER};

int gamemode;

void mainmenu(){
    int current_speed = 3;
    int current_difficulty = 2;
    char *difficulty_options[4] = { "EASY", "MEDIUM", "HARD", "BRUTAL"};
    int difficultyoptionsarray[] = {1, 2, 3, 7};
    int speed_options[4] = { 1, 2, 3 ,4};

	int option_row_pos = 27 + 17;
	
	gamemode = SINGLEPLAYER;

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
    		//if (use_default_colors () == ERR)
    			bg_color = COLOR_BLACK;
    		//else
    			//bg_color = -1;

    		// Start support for colors (Name, Foreground, Background)
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
    	attrset(COLOR_PAIR(RED_BLACK)); attron( A_BOLD);
mvaddstr( 5, 2 + 0, "8888888 8888888888 8 888888888o.      ,o888888o.     b.             8 ");
mvaddstr( 5, 2 + 1, "      8 8888       8 8888    `88.  . 8888     `88.   888o.          8 ");
mvaddstr( 5, 2 + 2, "      8 8888       8 8888     `88 ,8 8888       `8b  Y88888o.       8 "); 
mvaddstr( 5, 2 + 3, "      8 8888       8 8888     ,88 88 8888        `8b .`Y888888o.    8 "); 
mvaddstr( 5, 2 + 4, "      8 8888       8 8888.   ,88' 88 8888         88 8o. `Y888888o. 8 "); 
mvaddstr( 5, 2 + 5, "      8 8888       8 888888888P'  88 8888         88 8`Y8o. `Y88888o8 "); 
mvaddstr( 5, 2 + 6, "      8 8888       8 8888`8b      88 8888        ,8P 8   `Y8o. `Y8888 "); 
mvaddstr( 5, 2 + 7, "      8 8888       8 8888 `8b.    `8 8888       ,8P  8      `Y8o. `Y8 "); 
mvaddstr( 5, 2 + 8, "      8 8888       8 8888   `8b.   ` 8888     ,88'   8         `Y8o.` "); 
mvaddstr( 5, 2 + 9, "      8 8888       8 8888     `88.    `8888888P'     8            `Yo "); 

            int i, j;
            for (i=SCREENHEIGHT - 6; i<SCREENHEIGHT-1; i++){
                for (j=0; j<SCREENWIDTH; j++){
                    attrset(COLOR_PAIR(BLACK_WHITE));
                    mvaddch( j, i, ' '); 
                }
            }
            
            
            attrset(COLOR_PAIR(BORDER));
            int y;
            for (y=0; y<SCREENHEIGHT; y++){
                mvaddch (0, y, ' ');
                
                mvaddch (SCREENWIDTH - 1, y, ' ');
            }

            int x;
            for (x=0; x<SCREENWIDTH; x++){
                mvaddch (x, 0, ' ');
                
                mvaddch (x, SCREENHEIGHT - 1, ' ');
            }
            
            attron( A_DIM);
            mvprintw(SCREENWIDTH - 51, SCREENHEIGHT - 1, "Space/Enter: Start Game      P: Pause      Q: Quit");
    
            attrset(COLOR_PAIR(YELLOW_BLACK));
            attron( A_BOLD);
    		
		mvaddstr(7, 14, "GAME MODE:");
    		if (gamemode == SINGLEPLAYER)
    		{
    			attrset (COLOR_PAIR (WHITE_BLACK));attron( A_BOLD);
    			mvaddstr(7, 14+1, "One Player");
    
    			attrset(COLOR_PAIR(YELLOW_BLACK));
    			mvaddstr(7, 14+2, "Two Players");
    		}
    		else
    		{
    		    attrset(COLOR_PAIR(YELLOW_BLACK));
    		    mvaddstr(7, 14+1, "One Player");
    		    
    		    attrset (COLOR_PAIR (WHITE_BLACK));attron( A_BOLD);
    		    mvaddstr(7, 14+2, "Two Players");
    		}
    		
    		attrset(COLOR_PAIR(RED_BLACK)); attron( A_BOLD);
    		mvaddstr(27, 14, "GAME SETTINGS:");
    		attrset(COLOR_PAIR(GREEN_BLACK));
    		
    		//Single Player Options    
            if (gamemode == SINGLEPLAYER){
        		// Draw the level numbers
        		attron( A_BOLD);
        		mvaddstr(27, 14+2, "Difficulty:");
        
        		// Draw the options with the right colors
        		for (i = 0, j = 0; i < 4; i++)
        		{
        		    if (i == (current_difficulty-1))
        				{attrset (COLOR_PAIR (WHITE_BLACK));attron( A_BOLD);}
        			else
        				attrset(COLOR_PAIR(GREEN_BLACK));
        				
        			mvprintw(14 + 2, option_row_pos+j, "%s", difficulty_options[i]);	
        			if (i == 1)
        			    j += 9;
        			else
        			    j += 7;
        		}
    		}
    		else{
    		attrset(COLOR_PAIR(GREEN_BLACK));
        		mvaddstr(27, 14+2, "Blue: W-S-A-D     Red: Up-Down-Left-Right");
            }
            
    		attrset (COLOR_PAIR (CYAN_BLACK));
    		attron( A_BOLD);
    		mvaddstr(27, 14+1, "Speed:");
    
            // Draw the options with the right colors
    		for (i = 0, j = 0; i < 4; i++)
    		{
    		    if (i == (current_speed-1))
    				{attrset (COLOR_PAIR (WHITE_BLACK));attron( A_BOLD);}
    			else
    				attrset (COLOR_PAIR (CYAN_BLACK));
    				
    			mvprintw(14+1, option_row_pos+j, "%d", speed_options[i]);	
    			if (i == 1)
    			    j += 9;
    			else
    			    j += 7;
    		}
    		
    		
    		wait = getinput(&current_speed,&current_difficulty);
        	refresh ();
    	}
    
    	game.speed = current_speed;
    	game.difficulty = difficultyoptionsarray[current_difficulty - 1];
    	game.state = gamemode;
    	//Turns off all attributes
    	standend();
    	
    	
    	while (game.state == SINGLEPLAYER)    Oneplayergame();
    	while (game.state == TWOPLAYER)     Twoplayergame();
    }
}



int getinput(int* speed_cur_option, int* diff_cur_option)
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
		//if (gamemode == Twoplayergame)
			gamemode = SINGLEPLAYER;
		break;

	case KEY_DOWN:
		//if (gamemode == Oneplayergame)
			gamemode = TWOPLAYER;
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
		*speed_cur_option = (input - '0'); // ASCII table value
		break;

	default:
		break;
	}

	return TRUE;
}



void PauseGame(){
	nodelay(stdscr, FALSE);
	getch();
	nodelay(stdscr, TRUE);
}


void endprint(int highlight)
{
        int x, y, i;
        char *choices[] = {
                        "PLAY AGAIN.!",
                        "BACK TO MENU",
                  };
        int size_choices[] = { 12, 12};

        mvaddstr( 25, 6," ____________________________ ");
        for ( i=1; i<= 10 ; i++){
                mvaddch( 25, 6 + i,'|');
                mvaddch( 54, 6 + i,'|');
        }
        mvaddstr(25, 16, "|____________________________|");

        for(i = 0; i < 2; ++i)
        {
                x=(( 30 - size_choices[i])/2 + 25);
                y= 6+(10-2)/2 +i;
                if(highlight == i + 1)
                {       attron( A_STANDOUT); attron( A_BOLD);
                        mvprintw( x, y, "%s", choices[i]);
                        attroff( A_STANDOUT);
                }
                else{
                    attron( A_BOLD);
                        mvprintw( x, y, "%s", choices[i]);
                }
        }
        attron( A_BOLD);
        if (game.winner == 1 ){
                if (game.state == TWOPLAYER) mvprintw( (30 - 18)/2 + 25, 16-1,"BLUE PLAYER WINS!!!");
                else if (game.state == SINGLEPLAYER) mvprintw( (30 - 10)/2 + 25, 16-1,"YOU WON!!!");
        }
        else if (game.winner == 2 ){

                if (game.state == TWOPLAYER) mvprintw( (30 - 17)/2 + 25, 16-1,"RED PLAYER WINS!!!");
                else if (game.state == SINGLEPLAYER) mvprintw( (30 - 11)/2 + 25, 16-1,"YOU LOST :D");
        }
        else
                mvprintw( (30 - 9)/2 + 25, 16-1,"DRAW GAME");
        attroff( A_BOLD);
        refresh();
}


void printwinner(){

	init_pair (RED_BLACK,   COLOR_RED,   COLOR_BLACK);
	init_pair (BLUE_BLACK,  COLOR_BLUE,  COLOR_BLACK);
	if (game.winner == 1 ){
		attrset(COLOR_PAIR(BLUE_BLACK)); 
		attron( A_BOLD);
		if (game.state == TWOPLAYER) 
			mvprintw( 35, 16,"BLUE PLAYER WINS!!!");
		else if (game.state == SINGLEPLAYER) 
			mvprintw((30 - 10)/2 + 25, 16-1,"YOU WON!!!");
	}
	else if (game.winner == 2 ){
		attrset(COLOR_PAIR(RED_BLACK)); 
		attron( A_BOLD);
		if (game.state == TWOPLAYER) 
			mvprintw( (30 - 17)/2 + 25, 16-1,"RED PLAYER WINS!!!");
		else if (game.state == SINGLEPLAYER) 
			mvprintw( (30 - 11)/2 + 25, 16-1,"YOU LOST :D");
	}
	refresh();
}


void endgame()
{
        int highlight = 1;
        int choice = 0;
        int c;

        startmenu();   //set delay for menu

        endprint(highlight);
        while(1)
        {
            refresh();
            c = getch();

                switch(c)
                {
                    case KEY_UP:
                                if(highlight == 2)
                                        highlight = 1;
                                break;
                        case KEY_DOWN:
                                if(highlight == 1)
                                        highlight = 2;
                                break;
                        case 10:    case ' ':
                                choice = highlight;
                                break;
                        case 'q':       case 'Q':
                    ExitGame();
                    break;
                }
                endprint(highlight);
                if(choice == 1){      /* Player chose to 1*/
                        //Turn off all attributes
                        standend();
                        break;
            }
            else if(choice == 2){
                game.state = MAIN_MENU;
                //Turn off all attributes
                        standend();
                break;
            }
        }

        refresh();
        return;
}

