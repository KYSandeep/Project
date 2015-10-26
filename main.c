#include<stsdio.h>
#include<ncurses.h>
#include"bike.h"

void ExitGame(){
    endwin();
    exit(0);
}
            
void Twoplayergame(){
	gameinit();
	game.state = TWOPLAYER;
	
	int c, newdirection;
	queue player1, player2;
	int buffer1[MAXQSIZE], buffer2[MAXQSIZE];
	initqueue(&player1, buffer1, MAXQSIZE);	
	initqueue(&player2, buffer2, MAXQSIZE);	
	while(bike1.alive == 1 && bike2.alive == 1){
		usleep(30000);
		while((c = getch() != ERR)){
			switch(c){
				 case KEY_UP:
                    			if (player2.lastenqueued != UP) 
						enqueue (&player2, UP);
                    			break;

                		case KEY_LEFT:
                    			if (player2.lastenqueued != LEFT) 
						enqueue (&player2, LEFT);
                    			break;

                		case KEY_DOWN:
                    			if (player2.lastenqueued != DOWN) 
						enqueue (&player2, DOWN);
                   			 break;

                		case KEY_RIGHT:
                    			if (player2.lastenqueued != RIGHT) 
						enqueue (&player2, RIGHT);
                    			break;
                		case 'w': case 'W':
                    			if (player1.lastenqueued != UP) 
						enqueue (&player1, UP);
					break;
                		case 's': case 'S':
                    			if (player1.lastenqueued != DOWN) 
						enqueue (&player1, DOWN);
					break;
                		case 'a': case 'A':
                    			if (player1.lastenqueued != LEFT) 
						enqueue (&player1, LEFT);
					break;
                		case 'd': case 'D':
                    			if (player1.lastenqueued != RIGHT) 
						enqueue (&player1, RIGHT);
					break;
				case 'q' case 'Q':
					ExitGame();
					break;
				case 'p'case 'P':
					PauseGame();
					break;
				default:
					break;

			}
		
		}	
	gamewinner();
	printwinner();
	usleep(30000);
	endgame();
	return;
	}
	
} 

int main(){
	mainmenu();
	worksinit();
	ExitGame();

}
