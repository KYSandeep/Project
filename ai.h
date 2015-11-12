#ifndef AI_DEFINED
#define AI_DEFINED


#define LEFTTURN -1
#define STRAIGHT 0
#define RIGHTTURN 1
#define FG futuregame


extern int doneflag;


#include "works.h"
#include "bike.h"

struct future{
	char map[SCREENWIDTH][SCREENHEIGHT];
	struct snakestructure bot;
	struct snakestructure usr;
    
    int botdistancemap[SCREENWIDTH][SCREENHEIGHT];
    int usrdistancemap[SCREENWIDTH][SCREENHEIGHT];
};
	

void* aiProcessGame(void *data);
int aiMinimax(struct snakestructure* botsnakepointer, struct snakestructure* usrsnakepointer);
int aiMaxOf3( int *);
int aiScore( struct future futuregame, int direction, int depth, int alpha, int beta);
int aiSubScore( struct future futuregame, int direction, int depth, int alpha, int beta);

int aiDijkstra(char map[SCREENWIDTH][SCREENHEIGHT], int distance[SCREENWIDTH][SCREENHEIGHT], int start_x, int start_y);
int aiVoronoi(struct future* FGptr);

void aiUnlockMutex(void*);


#define aiMaxOf3(m_arr) ( m_arr[2]>m_arr[((m_arr[1]>m_arr[0])?1:0)])?2:((m_arr[1]>m_arr[0])?1:0)

#define aiMinOf3(m_arr) ( m_arr[2]<m_arr[((m_arr[1]<m_arr[0])?1:0)])?2:((m_arr[1]<m_arr[0])?1:0)


#define aiElongate(m_snake) {                                                            \
                    MovePoint (m_snake.head, m_snake.direction % 2, m_snake.direction / 2); \
                                                                                            \
                    if (FG.map[m_snake.head.x][m_snake.head.y] != 0) {                    \
                        m_snake.alive = 0;                                                  \
                        }                                                                   \
                                                                                            \
                    FG.map[m_snake.head.x][m_snake.head.y] = m_snake.marker;             \
                    m_snake.size++;                                                         \
                                                                                            \
                }


#endif
