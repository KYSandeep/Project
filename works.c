#include<stdio.h>
#include<ncurses.h>
#include<stdlib.h>
#include"works.h"
#include"bike.h"

void gameinit(){
	initscr();
	int height, width;
	getmaxyx(stdscr, height, width);
	start_color();
	 
	if ((width < SCREENWIDTH) || (height < SCREENHEIGHT) || (SCREENHEIGHT < 24) || (SCREENWIDTH < 80)){
        	endwin();
        	printf ("Your console screen is smaller than %d x %d\nPlease resize your window and try again\n", SCREENWIDTH, SCREENHEIGHT);
        	printf("The set SCREENWIDTH and SCREENHEIGHT in for the game must be greater than 24x80\n");
		exit();
	}
	raw();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	nodelay(stdscr, TRUE);
	refresh();
	
}

void startgame(){ 
	nodelay(stdscr, TRUE);
    	clearscreen();
    	makewalls();
    	bikeinit();
    	//game.depth = game.difficulty;
    

    	init_pair(BIKE1_COLORCODE, COLOR_BLUE, COLOR_BLUE);
    	init_pair(BIKE2_COLORCODE, COLOR_RED, COLOR_RED);
    	init_pair(BIKE1HEAD_COLORCODE, COLOR_BLUE, COLOR_BLUE);
    	init_pair(BIKE2HEAD_COLORCODE, COLOR_RED, COLOR_RED);
    	init_pair(WALL_COLORCODE, COLOR_WHITE, COLOR_WHITE);
    	init_pair(OUTSIDE_COLORCODE, COLOR_BLACK, COLOR_BLACK);

    	refresh();
    	flushinp();
	return;

}


void startmenu(){

	nodelay(stdscr, FALSE);
		
	erase();
	refresh();
	flushimp();
	return;
}

void walls(){

        WINDOW *my_win;
        int startx, starty, width, height;
        int ch;

        //cbreak();                       /* Line buffering disabled, Pass on
        height = 24;
        width = 80;
        //starty = (LINES - height) / 2;  /* Calculating for a center placement */
        //startx = (COLS - width) / 2;    /* of the window                */
        my_win = newwin(height, width, starty, startx);
        box(my_win, 0 , 0);          /* 0, 0 gives default characters 
                                         * for the vertical and horizontal
                                         * lines                        */
        wrefresh(my_win);
         return;

}


void worksclearmap(){
    int i, j;
    for (i=0; i<SCREENWIDTH; i++){
        for (j=0; j<SCREENHEIGHT; j++){
            game.map[i][j] = 0;
        }
    }
}



void gamewinner(){
    	if ((bike1.head.x == bike2.head.x) && (bike1.head.y == bike2.head.y)) 
		bike1.alive = bike2.alive = 0;
    	if (bike1.alive != 0) 
		game.winner = 1;
    	else if (bike2.alive != 0) 
		game.winner = 2;
    	else game.winner = 0;
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
