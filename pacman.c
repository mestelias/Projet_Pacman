#include "pacman.h"
#include "primitives.h"

//fonction qui s'occupe de dessiner le pacman en fonction de son orientation de la bouche
void drawPacman(pacman p)
{
    float angle;
    GLubyte r = 255, g = 255, b = 0;
    int ray = 15;
    float valueD, valueF;

    if(p.orientation == 'R')
    {
        valueD = 0.5f;
        valueF = 1.8f;
    }
    if(p.orientation == 'L')
    {
        valueD = -2.5f;
        valueF = 0.8f;
    }
    if(p.orientation == 'U')
    {
        valueD = 2.2f;
        valueF = 2.3f;
    }
    if(p.orientation == 'D')
    {
        valueD = -1.0f;
        valueF = 1.3f;
    }
    if(p.bouche == 0)
    {
        valueD = 0.0f;
        valueF = 2.0f;
    }
    for(angle = valueD; angle < valueF * M_PI; angle += 0.005f)
    {
        drawLine(p.position_x * 30 + 15, p.position_y * 30 + 15, p.position_x * 30 + 15 + ray * cos(angle), p.position_y * 30 + 15 + ray * sin(angle), RGB(r, g, b));
    }
}

//fonction qui permet de mettre en mouvement le pacman en testant plusieurs conditions
void movePacman(pacman *p, labyrinthe laby, int deplacement_x, int deplacement_y, int *score, int *decompteur)
{
    if(p->position_x + deplacement_x == laby.maximum_i)
    {
        if(laby.l[p->position_x][p->position_y] != 0 && laby.l[p->position_x][p->position_y] != 9)
        {
            (*score)++;
        }
        laby.l[p->position_x][p->position_y]&= 0;
        p->position_x = 0;
        p->orientation = 'L';
        p->bouche = (p->bouche + 1) % 2;

        return;
    }
    if(p->position_x + deplacement_x < 0)
    {
        if(laby.l[p->position_x][p->position_y] != 0 && laby.l[p->position_x][p->position_y] != 9)
        {
            (*score)++;
        }
        laby.l[p->position_x][p->position_y]&= 0;
        p->position_x = laby.maximum_i - 1;
        p->orientation = 'R';
        p->bouche = (p->bouche + 1) % 2;

        return;   
    }
    if(deplacement_x == 0 && deplacement_y == 0)
    {
        return;
    }
    if(laby.l[p->position_x + deplacement_x][p->position_y + deplacement_y] != -1 && laby.l[p->position_x + deplacement_x][p->position_y + deplacement_y] != 9)
    {
        if(laby.l[p->position_x][p->position_y] != 0 && laby.l[p->position_x][p->position_y] != 9)
        {
            (*score)++;
        }
        if(laby.l[p->position_x][p->position_y] == 5)
        {
            *decompteur = 50;
        }
        laby.l[p->position_x][p->position_y]&= 0;
        p->position_x += deplacement_x;
        p->position_y += deplacement_y;
        p->bouche = (p->bouche + 1) % 2;
        if(deplacement_x == 1)
        {
            p->orientation = 'R';
        }
        else {if(deplacement_x == -1)
        {
            p->orientation = 'L';
        }
        else {if(deplacement_y == 1)
        {
            p->orientation = 'U';
        }
        else {if(deplacement_y == -1)
        {
            p->orientation = 'D';
        }}
    }}
    }
}