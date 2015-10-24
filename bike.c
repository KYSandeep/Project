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
	bike2.marker = BIKE2.MARKER;
	
	bike1.tailcolor = BIKE1_TAILCOLOR;
	bike2.tailcolor = BIKE2_TAILCOLOR;

}
