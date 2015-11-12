#include<stdio.h>
#include<ncurses.h>
#include<stdlib.h>
#include<pthread.h>
#include"works.h"
#include"bike.h"
#include"ai.h"


void gameinit(){
	initscr();
	int height, width;
	getmaxyx(stdscr, height, width);
	start_color();
	 
	if ((width < SCREENWIDTH) || (height < SCREENHEIGHT) || (SCREENHEIGHT < 24) || (SCREENWIDTH < 80)){
        	endwin();
        	printf ("Your console screen is smaller than %d x %d\nPlease resize your window and try again\n", SCREENWIDTH, SCREENHEIGHT);
        	printf("The set SCREENWIDTH and SCREENHEIGHT in for the game must be greater than 24x80\n");
		exit(0);
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
    	worksclearmap();
    	walls();
    	bikeinit();
    	game.depth = game.difficulty;
    

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
	flushinp();
	return;
}

void walls(){

    attrset(COLOR_PAIR(OUTSIDE_COLORCODE));
    erase();
    bkgd(COLOR_PAIR(OUTSIDE_COLORCODE));
    
    attrset(COLOR_PAIR(WALL_COLORCODE));
    //Draw vertical walls
    int y;
    for (y=0; y<SCREENHEIGHT; y++){
        mvaddch (0, y, WALLCHAR);
        game.map[0][y] = WALL;
        
        mvaddch (SCREENWIDTH - 1, y, WALLCHAR);
        game.map[SCREENWIDTH-1][y] = WALL;
    }

    //Draw horizontal walls
    int x;
    for (x=0; x<SCREENWIDTH; x++){
        mvaddch (x, 0, WALLCHAR);
        game.map[x][0] = WALL;
        
        mvaddch (x, SCREENHEIGHT - 1, WALLCHAR);
        game.map[x][SCREENHEIGHT-1] = WALL;
    }

    return;

}


void worksclearmap(){
    int i, j;
    for (i=0; i < SCREENWIDTH; i++){
        for (j=0; j < SCREENHEIGHT; j++){
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

void engineSleepAndCallBot( bikestruct* botbikepointer, bikestruct* usrbikepointer, long int usleeptime){
    struct timespec timeout;
    pthread_t aithread;
    int error = 0;
    void *exitstatus;

    static int counter;

    botbikepointer->new_direction = botbikepointer->direction;

    bikestruct* bikes[] = {botbikepointer, usrbikepointer};

    doneflag = 0;
    pthread_create(&aithread, NULL, aiProcessGame, bikes);

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




void initqueue (queue* q, int* array, int arraysize){
	q->size = q->front = q->behindback = 0;
	q->maxqsize = arraysize;
	if (array != NULL){
		q->data = array;
	}
	else{
		q->data = (int*) malloc ((q->maxqsize + 1) * sizeof(int));
	}
}

void enqueue (queue* q, int val){
	if ((q->size == 0) || (q->behindback != q->front)){
		q->size++;
		q->data[q->behindback] = val;
		q->lastenqueued = val;
		q->behindback = (q->behindback + 1) % q->maxqsize;
	}
}

int dequeue (queue* q){
	if (q->size > 0){
		q->size--;
		int returnvalue = q->data[q->front];
		q->front = (q->front + 1) % q->maxqsize;
		return returnvalue;
	}
	else return 0;
}


void freequeue (queue* q){
	free(q->data);
}
