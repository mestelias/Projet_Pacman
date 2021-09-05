#include <GL4D/gl4dp.h>

typedef struct labyrinthe labyrinthe;

struct labyrinthe
{
    int **l;
    int maximum_i;
    int maximum_j;
};

extern void drawLabyrinthe(labyrinthe laby);
extern int ** inititalisationLabyrinthe();