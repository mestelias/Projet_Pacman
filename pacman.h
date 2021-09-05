#include <GL4D/gl4dp.h>
#include "labyrinthe.h"

typedef struct pacman pacman;

struct pacman
{
    int position_x;
    int position_y;
    char orientation;
    int bouche;
};

extern void drawPacman(pacman p);
extern void movePacman(pacman *p, labyrinthe laby, int deplacement_x, int deplacement_y, int *score, int *decompteur);