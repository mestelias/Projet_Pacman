#include "labyrinthe.h"
#include "primitives.h"

//parcours du tableau qui permettra de dessiner le labyrinthe
void drawLabyrinthe(labyrinthe laby)
{
    int i, j;
    for(i = 0; i < laby.maximum_i; i++)
    {
        for (j = 0; j < laby.maximum_j; j++)
        {
            if(laby.l[i][j] == -1)
            {
                mur(i, j);
            } 
            else {if(laby.l[i][j] == 1)
            {
                nourriture(i, j);
            }
            else {if(laby.l[i][j] == 5)
            {
                nourritureMagique(i, j);
            }}
        }}
    }
}

//initialisation du labyrinthe en utilisant un tableau statique
int ** inititalisationLabyrinthe()
{
    int **l = malloc(27 * sizeof(int*));
    for(int i = 0; i < 27; i++)
    {
        l[i] = malloc(21 * sizeof(int));
    }

    int a [21][27] = {
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5,-1},
        {-1, 1,-1,-1,-1, 1,-1,-1,-1,-1,-1,-1, 1,-1, 1,-1,-1,-1,-1,-1,-1, 1,-1,-1,-1, 1,-1},
        {-1, 1,-1,-1,-1, 1,-1,-1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1,-1,-1, 1,-1,-1,-1, 1,-1},
        {-1, 1,-1,-1,-1, 1,-1,-1,-1, 1,-1,-1,-1,-1,-1,-1,-1, 1,-1,-1,-1, 1,-1,-1,-1, 1,-1},
        {-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1},
        {-1, 1,-1,-1,-1, 1,-1,-1,-1,-1,-1,-1, 1,-1, 1,-1,-1,-1,-1,-1,-1, 1,-1,-1,-1, 1,-1},
        {-1, 5, 1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1, 5,-1},
        {-1,-1,-1,-1,-1,-1,-1, 1,-1, 1,-1,-1, 9, 9, 9,-1,-1, 1,-1, 1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1, 1,-1, 1,-1, 9, 9, 9, 9, 9,-1, 1,-1, 1,-1,-1,-1,-1,-1,-1,-1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1, 9, 9, 9, 9, 9,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {-1,-1,-1,-1,-1,-1,-1, 1,-1, 1,-1, 9, 9, 9, 9, 9,-1, 1,-1, 1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1, 1,-1, 1,-1,-1,-1,-1,-1,-1,-1, 1,-1, 1,-1,-1,-1,-1,-1,-1,-1},
        {-1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5,-1},
        {-1, 1,-1,-1,-1, 1,-1,-1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1,-1,-1, 1,-1,-1,-1, 1,-1},
        {-1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1, 1, 1, 1,-1},
        {-1,-1,-1, 1,-1,-1,-1, 1,-1, 1,-1,-1,-1,-1,-1,-1,-1, 1,-1, 1,-1,-1,-1, 1,-1,-1,-1},
        {-1, 1, 1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1,-1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1, 1,-1},
        {-1, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 1,-1, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 1,-1},
        {-1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    };

    int s = 0;
    for(int i = 0; i < 21; i++)
    {
        for(int j = 0; j < 27; j++)
        {
            l[j][i] = a[20 - i][j];
            if(l[j][i] == 1)
            {
                s++;
            }
        }
    }
    return l;
}