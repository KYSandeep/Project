#ifdef works_defined
#define works_define

#define SCREENWIDTH 80
#define SCREENHEIGHT 24

#define MAXSQUARES (SCREENWIDTH*SCREENHEIGHT)

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

#define mvaddch(mpoint, msymbol) mvaddch(mpoint.y, mpoint.x, msymbol)

#define MAXQSIZE 10

typedef struct queue {
	int *data;
	int maxqsize;
	int front;
	int behindback;
	int lastenqeued;
	int size;
}queue;


void initqueue(queue* q, int* array, int n);
void enqueue(queue* q, int val);
void dequeue(queue* q);
void freequeue(queue* q);

#endif
