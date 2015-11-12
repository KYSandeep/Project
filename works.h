#ifndef works_define
#define works_define

#define SCREENWIDTH 80
#define SCREENHEIGHT 24

#define MAXSQUARES (SCREENWIDTH*SCREENHEIGHT)

#define WALL '*'
#define WALLCHAR ' '
#define BIKEHEAD ' '
#define BIKEBODY ' '


#define BIKE1_COLORCODE 1
#define BIKE2_COLORCODE 2
#define WALL_COLORCODE 3
#define OUTSIDE_COLORCODE 7
#define BIKE1HEAD_COLORCODE 5
#define BIKE2HEAD_COLORCODE 6
#define COLOR_GREY 8

typedef struct gamestructure {
	char state;
	char speed;
	int difficulty;
	int depth;
	char winner;
	char map[SCREENWIDTH][SCREENHEIGHT];

}gamestructure;


#define SINGLEPLAYER 1
#define TWOPLAYER 2
#define PAUSED 3
#define MAIN_MENU 4
#define END_MENU 5


#define GAMEDELAY (50000 * (5 - game.speed))
#define MAXKEYSIZE 3
#define ENGINETIMEOUTCOUNTER 30

#define PLAYER1 1
#define PLAYER2 2
#define DRAW 0

extern gamestructure game;

void startgame();
void startmenu();
void walls();
void worksclearmap();
void gamewinner();
//void engineSleepAndCallBot(bikestruct* botbikepointer, bikestruct* usrbikepointer, long int usleeptime);

#define mvaddchar(mpoint, msymbol) mvaddch(mpoint.y, mpoint.x, msymbol)
#define MAXQSIZE 10
typedef struct queue {
	int* data;
	int maxqsize;
	int front;
	int behindback;
	int lastenqueued;
	int size;
} queue;


void initqueue(queue* q, int* array, int n);
void enqueue(queue* q, int val);
int dequeue(queue* q);
void freequeue(queue* q);

#endif
