#include<ncurses.h>
#include"bike.h"
#include"works.h"

bikestruct bike1;
bikestruct bike2;


void bikeinit(){
	bike1.size = bike1.alive = bike2.size = bike2.alive = 1;
	setpoint(bike1.head, BIKE1_STARTX, BIKE1_STARTY);
	setpoint(bike2.head, BIKE2_STARTX, BIKE2_STARTY);
	
	bike1.marker = BIKE1_MARKER;
	bike2.marker = BIKE2_MARKER;
	
	bike1.tailcolor = BIKE1_COLORCODE;
	bike2.tailcolor = BIKE2_COLORCODE;
	
	bike1.headcolor = BIKE1HEAD_COLORCODE;
	bike2.headcolor = BIKE2HEAD_COLORCODE;
	
	game.map[bike1.head.x][bike1.head.y] = bike1.marker;
	game.map[bike2.head.x][bike2.head.y] = bike2.marker;
	
	bike1.direction = bike1.new_direction = BIKE1_STARTDIR;
	bike2.direction = bike2.new_direction = BIKE2_STARTDIR;
	
	mvaddch(bike1.head, BIKEHEAD);
	mvaddch(bike2.head, BIKEHEAD);
	
	
}
