#include<stsdio.h>
#include<ncurses.h>
#include"bike.h"

void ExitGame(){
    endwin();
    exit(0);
}
            

int main(){
	worksinit();
	ExitGame();

}
