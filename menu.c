#include <curses.h>
#include "menu.h"
#include "works.h"
#include "tron.h"

void PauseGame(){
	nodelay(stdcr, FALSE);
	getch();
	nodelay(stdscr, TRUE);
}


void printwinner(){
	

}
