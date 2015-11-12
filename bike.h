#ifndef BIKEDEFINED
#define BIKEDEFINED

#define UP -2
#define DOWN 2
#define LEFT -1
#define RIGHT 1
	
#define BIKE1_STARTX 4
#define BIKE2_STARTX (SCREENWIDTH - 5)
#define BIKE1_STARTY (SCREENWIDTH - 5)
#define BIKE2_STARTY (SCREENWIDTH - 5)
#define BIKE1_STARTDIR RIGHT
#define BIKE2_STARTDIR LEFT
#define BIKE1_MARKER 1
#define BIKE2_MARKER 2

#define MAXSIZE (MAXSQUARES / 2)

struct point {
	int x;
	int y;
};

typedef struct bikestruct{
	char alive;
	struct point head;
	int direction;
	int size;
	char marker;
	char tailcolor;
	char headcolor;
	int new_direction;
}bikestruct;

#define setpoint(mpoint, mx, my) mpoint.x = mx; mpoint.y = my
#define movepoint(mpoint, mx, my) mpoint.x += mx; mpoint.y += my
#define equatepoint(mpoint1, mpoint2) mpoint1.x = mpoint2.x; mpoint1.y = mpoint2.y

extern bikestruct bike1;
extern bikestruct bike2;
	

void bikeinit();

#define bikeIsDirectionAllowed(macrobike, macrodirection) (macrobike.direction + macrodirection != 0)

#define bikeUpdateDirection(macrobike, macrodirection)  if (macrobike.direction + macrodirection != 0) {macrobike.direction = macrodirection;}


#define bikelong(mbike) { attrset(COLOR_PAIR(mbike.tailcolor));				\
				 mvaddchar(mbike.head, BIKEBODY);			\
			movepoint(mbike.head, mbike.direction % 2, mbike.direction / 2); \
			if(game.map[mbike.head.x][mbike.head.y] != 0){	mbike.alive = 0;}\
			game.map[mbike.head.x][mbike.head.y] = mbike.marker;		\
			attrset(COLOR_PAIR(mbike.headcolor));				\
			mvaddchar(mbike.head, BIKEHEAD);				\
			mbike.size++;						\
		}
				
		

	
#endif
