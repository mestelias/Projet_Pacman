#include <GL4D/gl4dp.h>
#include "pacman.h"

typedef struct fantome fantome;

struct fantome 
{
    int position_x;
    int position_y;
    int deplacement_x;
    int deplacement_y;
    int identifiant;
    int etat;
};

extern void drawFantome(fantome f);
extern void moveFantome(fantome *f, labyrinthe laby, pacman p, int *deplacement_x, int *deplacement_y, int collision);