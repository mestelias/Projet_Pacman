#include "fantome.h"
#include "primitives.h"
#include "pile.h"
#include <string.h>

static void deplacementPlusCourtChemin(fantome *f ,labyrinthe laby, pacman p, int *deplacement_x, int *deplacement_y);
static void deplacementAleatoire(fantome *f ,labyrinthe laby, pacman p, int *deplacement_x, int *deplacement_y);

//fonction qui permet d'analyser le labyrinthe
static void subPlusCourtChemin(int **l, int v, int x0, int y0, int x1, int y1, int w)
{
    int i;
    const int d[][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    l[y0][x0] = v++;
    if(x0 == x1 && y0 == y1)
    {
        return;
    } 
    for(i = 0; i < 4; ++i)
    {
        int nx = x0 + d[i][0];
        int ny = y0 + d[i][1];

        if((ny > 0 && ny < 21 && nx > 0 && nx < 27) && (l[ny][nx] != -1) && (l[ny][nx] == 0 || l[ny][nx] > v))
        {
            subPlusCourtChemin(l, v, nx, ny, x1, y1, w);
        }
    }
}

//fonction qui permet de recuperer le resultat de l'analyse de la fonction precedente
static void plusCourtChemin(labyrinthe laby, int x0, int y0, int x1, int y1)
{
    int **copy = malloc(27 * sizeof(int *));

    for(int i = 0; i < 21; i++)
    {
        copy[i]= malloc(27 * sizeof(int));
    }
    for(int i = 0; i < 21; i++)
    {
        for(int j = 0; j < 27; j++)
        { 
            if(laby.l[j][i] == -1)
            {
                copy[i][j] = -1;
            }
            else
            {
                copy[i][j] = 0;
            }
        }
    }
    copy[9][0] = -1;
    copy[9][26] = -1;
    
    subPlusCourtChemin(copy, 1, x0, y0, x1, y1, 27);
    
    int i;
    const int d[][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    for(i = 0; i < 4; ++i)
    {
        int nx = x1 + d[i][0];
        int ny = y1 + d[i][1];
        if(copy[ny][nx] == copy[y1][x1] - 1)
        {
            x1 = nx;
            y1 = ny;
            break;
        }
    }
    push(y1);
    push(x1);
}

//fonction qui permet de dessiner les trois fantomes, sous forme de triangle rouge
void drawFantome(fantome f)
{
    int x = f.position_x * 30;
    int y = f.position_y * 30;
    vec4 v = {1.0f, 0.6f, 0.8f, 1.0f};
    if(f.etat == 0)
    {
        v.x = 1.0f;
        v.y = 1.0f;
        v.z = 0.0f;
    }
    else
    {
        if(f.identifiant == 1)
        {
            v.x = 1.0f;
            v.y = 0.0f;
            v.z = 0.0f;
        }
        if(f.identifiant == 2)
        {
            v.x = 1.0f;
            v.y = 0.0f;
            v.z = 0.0f;
        }
        if(f.identifiant == 3)
        {
            v.x = 1.0f;
            v.y = 0.0f;
            v.z = 0.0f;
        }
    }
    triangle_t a = 
    {
        {
            {x + 5, y + 5, v, {10.0f, 0.0f}},
            {x + 25, y + 5, v, {0.0f, 10.0f}}, 
            {x + 15, y + 25, v, {0.0f, 10.0f}}
        }
    };
    fillTriangle(&a);
}

//fonction qui permet de mettre en mouvement les fantomes, un fantome utilisera le chemin le plus court pour
// arriver jusuq'au pacman. Tandis que les deux autres auront un deplacement aleatoire
void moveFantome(fantome *f , labyrinthe laby, pacman p, int *deplacement_x, int *deplacement_y, int collision)
{ 
    if(f->etat == 0)
    {
        pacman p;
        p.position_y = 9;
        p.position_x = 12;
        int c = rand()%3;

        if(!c)
        {
            deplacementAleatoire(f, laby, p, deplacement_x, deplacement_y);
        }
        else
        {
            deplacementPlusCourtChemin(f, laby, p, deplacement_x, deplacement_y);
        }

        return;
    }

    if(f->identifiant == 1)
    {
        deplacementPlusCourtChemin(f, laby, p, deplacement_x, deplacement_y);
    }

    if(f->identifiant == 2)
    { 
        deplacementAleatoire(f, laby, p, deplacement_x, deplacement_y);
    }

    if(f->identifiant == 3)
    {
        int c = rand()%3;
        if(!c)
        {
            deplacementPlusCourtChemin(f, laby, p, deplacement_x, deplacement_y);
        }
        else 
        {
            deplacementAleatoire(f, laby, p, deplacement_x, deplacement_y);
        }
    }
}

//fonction qui permet d'utiliser le plus court chemin, qu'on utilise pour un fantome pour arriver jusqu'au
// pacman de maniere la plus courte possible
static void deplacementPlusCourtChemin(fantome *f ,labyrinthe laby,pacman p, int *deplacement_x, int *deplacement_y)
{
    if(p.position_x != 0 && p.position_x != 26 )
    {
        plusCourtChemin(laby, p.position_x,p.position_y, f->position_x , f->position_y);
        if(!empty())
        {
            f->position_x = pop();
            f->position_y = pop();
        }   
    }
}

//fonction qui permet le deplacement aleatoire qu'on utlise pour les deux autres fantomes
static void deplacementAleatoire(fantome *f , labyrinthe laby, pacman p, int *deplacement_x, int *deplacement_y)
{
    int d[][2] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
    if(f->position_x + *deplacement_x < 0)
    {
        *deplacement_x = 1;
    }
    else
    {
        if(f->position_x + *deplacement_x > 26)
        {
            *deplacement_x = -1;
        }
    }
    if(laby.l[f->position_x + *deplacement_x][f->position_y + *deplacement_y] == -1 || (*deplacement_x + *deplacement_y) == 0)
    {
        do
        {
            int c = rand()%4;
            *deplacement_x = d[c][0];
            *deplacement_y = d[c][1];
        }
        while(laby.l[f->position_x + *deplacement_x][f->position_y + *deplacement_y] == -1);
    }
    f->position_x = f->position_x + *deplacement_x;
    f->position_y = f->position_y + *deplacement_y;
}