#ifndef AI_DEFINED
#define AI_DEFINED


#define LEFTTURN -1
#define STRAIGHT 0
#define RIGHTTURN 1
#define FG futuregame


extern int doneflag;

struct future{
	char map[SCREENWIDTH][SCREENHEIGHT];
	bikestruct bot;
	bikestruct usr;
    
    int botdistancemap[SCREENWIDTH][SCREENHEIGHT];
    int usrdistancemap[SCREENWIDTH][SCREENHEIGHT];
};
	

void* aiProcessGame(void *data);
int aiMinimax(bikestruct* botbikepointer, bikestruct* usrbikepointer);
int aiMaxOf3( int *);
int aiScore( struct future futuregame, int direction, int depth, int alpha, int beta);
int aiSubScore( struct future futuregame, int direction, int depth, int alpha, int beta);

int aiDijkstra(char map[SCREENWIDTH][SCREENHEIGHT], int distance[SCREENWIDTH][SCREENHEIGHT], int start_x, int start_y);
int aiVoronoi(struct future* FGptr);

void aiUnlockMutex(void*);


#define aiMaxOf3(m_arr) ( m_arr[2]>m_arr[((m_arr[1]>m_arr[0])?1:0)])?2:((m_arr[1]>m_arr[0])?1:0)

#define aiMinOf3(m_arr) ( m_arr[2]<m_arr[((m_arr[1]<m_arr[0])?1:0)])?2:((m_arr[1]<m_arr[0])?1:0)


#define aiElongate(m_bike) {                                                            \
                    movepoint (m_bike.head, m_bike.direction % 2, m_bike.direction / 2); \
                                                                                            \
                    if (FG.map[m_bike.head.x][m_bike.head.y] != 0) {                    \
                        m_bike.alive = 0;                                                  \
                        }                                                                   \
                                                                                            \
                    FG.map[m_bike.head.x][m_bike.head.y] = m_bike.marker;             \
                    m_bike.size++;                                                         \
                                                                                            \
                }


#endif
