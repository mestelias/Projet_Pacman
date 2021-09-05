/*!\file window.c
 * \brief GL4Dummies, exemple simple 2D avec GL4Dummies
 * \author Farès BELHADJ, amsi@ai.univ-paris8.fr
 * \date February 04 2018, modified on March 06, 2020 by 
 * adding Visual Studio configuration files.
 */

/* inclusion des entêtes de fonctions de gestion de primitives simples
 * de dessin. La lettre p signifie aussi bien primitive que
 * pédagogique. */
#include <GL4D/gl4dp.h>
#include "primitives.h"

#include <time.h>
#include "fantome.h"


int deplacement_x = 0;
int deplacement_y = 0;
int a = 0;
int vie = 5;
int debut = 0;
int decompteur = 0;
int delta[][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
static void keyup(int keycode);

pacman p = {13, 7, 'R', 1};
fantome f = {12, 9, 0, 0, 1, 1};
fantome f1 = {13, 9, 0, 0, 2, 1};
fantome f2 = {14, 9, 0, 0, 3, 1};
labyrinthe laby;
int score = 0;

//fonction qui permet la remise en place du pacman et des fantomes apres qu'un ceux-ci mange le pacman
static void reinitialisation()
{
  vie--;
  if(!vie)
  {
    fprintf(stderr, "YOU LOSE !");
    vie = 5;
    laby.l = inititalisationLabyrinthe();
    score = 0;
  }
  deplacement_x = 0;
  deplacement_y = 0;
  a = 0;

  p.position_x = 13;
  p.position_y = 7;
  p.orientation = 'R';
  f.position_x = 12;
  f.position_y = 9;
  f1.position_x = 13;
  f1.position_y = 9;
  f2.position_x = 14;
  f2.position_y = 9;
  debut = 0;
}

//fonction qui gere les cas de collisions avec les fantomes, et donc remet le pacman et les fantomes 
// a leur place initiale apres une collision entre le pacman et un fantome
int collision()
{
  if((p.position_x == f.position_x && p.position_y == f.position_y) || (p.position_x == f1.position_x && p.position_y == f1.position_y) || (p.position_x == f2.position_x && p.position_y == f2.position_y))
  {
    if(p.position_x == f.position_x && p.position_y == f.position_y)
    {
      if(f.etat == 1)
      {
        reinitialisation();
      } 
      else
      {
        f.etat = 1;
        f.position_x = 12; 
        f.position_y = 9;
      }
    }
    if(p.position_x == f1.position_x && p.position_y == f1.position_y)
    {
      if(f1.etat == 1)
      {
        reinitialisation();
      }
      else
      {
        f1.etat = 1;
        f1.position_x = 13;
        f1.position_y = 9; 
      }
    }
    if (p.position_x == f2.position_x && p.position_y == f2.position_y)
    {
      if (f2.etat == 1)
      {
        reinitialisation();
      }
      else
      {
        f2.etat = 1;
        f2.position_x = 14;
        f2.position_y = 9;
      }
    }
    return 1;
  }
  return 0;
}

//fonction qui permet la mise en mouvement du pacman et des fantomes et de gerer les etats des fantomes 
// en fonction de la nourriture de la nourriture magique si elle est mange ou non par le pacman

unsigned int move(unsigned int intervalle, void * c)
{
  if (decompteur == 50)
  {
    f.etat = 0;
    f1.etat = 0;
    f2.etat = 0;
  }
  if(decompteur != 0)
  {
    decompteur--;
  }
  else
  {
    f.etat = 1;
    f1.etat = 1;
    f2.etat = 1;
  }
  if(debut)
  {
    movePacman(&p , laby, deplacement_x, deplacement_y, &score, &decompteur);
    if(collision())
    {
      return intervalle;
    }
    if(a == 0)
    {
      moveFantome(&f ,laby , p, &delta[1][0], &delta[1][1], 6);
      moveFantome(&f1 ,laby , p, &delta[0][0], &delta[0][1], 6);
      moveFantome(&f2 ,laby , p, &delta[2][0], &delta[2][1], 6);
      a = 1;
      if(collision())
      {
        return intervalle;
      }
    }
    else
    {
      a = 0;
    }
    if(score == 248)
    {
      fprintf(stderr, "YOU WIN !");
      score = 0;
      laby.l = inititalisationLabyrinthe();
      laby.maximum_i = 27;
      laby.maximum_j = 21;
      reinitialisation();
      if(vie != 5)
      {
        vie = 5;
        laby.l = inititalisationLabyrinthe();
        score = 0;
        p.orientation = 'R';
      }
    }
  }
  return intervalle;
}




/* inclusion des entêtes de fonctions de création et de gestion de
 * fenêtres système ouvrant un contexte favorable à GL4dummies. Cette
 * partie est dépendante de la bibliothèque SDL2 */
#include <GL4D/gl4duw_SDL2.h>

static void draw(void);

/*!\brief créé la fenêtre, un screen 2D effacé en noir et lance une
 *  boucle infinie.*/
int main(int argc, char ** argv) {
  laby.l = inititalisationLabyrinthe();
  laby.maximum_i = 27;
  laby.maximum_j = 21;
  
  
  /* tentative de création d'une fenêtre pour GL4Dummies */
  if(!gl4duwCreateWindow(argc, argv, /* args du programme */
			 "PACMAN", /* titre */
			 100, 100, 810,660, /* x,y, largeur, heuteur */
			 GL4DW_SHOWN) /* état visible */) {
    /* ici si échec de la création souvent lié à un problème d'absence
     * de contexte graphique ou d'impossibilité d'ouverture d'un
     * contexte OpenGL (au moins 3.2) */
     
    return 1;
  }
  
SDL_GL_SetSwapInterval(0);
  /* création d'un screen GL4Dummies (texture dans laquelle nous
   * pouvons dessiner) aux dimensions de la fenêtre */
  gl4dpInitScreen();
  //gl4dpInitScreenWithDimensions(160, 120);


  /* décommentez la ligne suivante pour effacer l'écran en bleu foncé. */
  //gl4dpClearScreenWith(RGB(0, 0, 155));

  gl4duwDisplayFunc(draw);
  gl4duwKeyUpFunc(keyup);
 
  /* boucle infinie pour éviter que le programme ne s'arrête et ferme
   * la fenêtre immédiatement */
  char c;
  SDL_AddTimer(100, move, &c);
  gl4duwMainLoop();
 
  return 0;
}

//fonction qui permet de donner une instruction lorqu'on presse une fleche de direction sur le clavier
static void keyup(int keycode) 
{  
  debut = 1;
  switch(keycode)
  {
    case GL4DK_ESCAPE:
    free(laby.l);
    exit(0);
    break;
    
    case GL4DK_LEFT:
    if(p.position_x + 1 != laby.maximum_i && p.position_x != 0 && laby.l[p.position_x - 1][p.position_y] != -1 && laby.l[p.position_x - 1][p.position_y] != 9)
    {
      deplacement_x = -1;
      deplacement_y = 0;
    }
    break;
    
    case GL4DK_RIGHT:
    if(p.position_x + 1 != laby.maximum_i && p.position_x != 0 && laby.l[p.position_x + 1][p.position_y] != -1 && laby.l[p.position_x + 1][p.position_y] != 9)
    {
      deplacement_x = 1;
      deplacement_y = 0;
    }   
    break;
    
    case GL4DK_DOWN:
    if(p.position_x + 1 != laby.maximum_i && p.position_x != 0 && laby.l[p.position_x][p.position_y - 1] != -1 && laby.l[p.position_x][p.position_y - 1] != 9)
    {
      deplacement_x = 0;
      deplacement_y = -1;
    } 
    break;
    
    case GL4DK_UP:
    if(p.position_x + 1 != laby.maximum_i && p.position_x != 0 && laby.l[p.position_x][p.position_y + 1] != -1 && laby.l[p.position_x][p.position_y + 1] != 9)
    { 
      deplacement_x = 0;
      deplacement_y = 1;
    }
    break;
  }
}

//fonction qui permet l'appel des fonction draw pour dessiner le labyrinthe, le pacman ainsi que les fantomes
void draw(void) {
  
  
  /* effacement du screen en cours en utilisant la couleur par défaut,
   * le noir */
  gl4dpClearScreen();
  
  drawLabyrinthe(laby);
  drawPacman(p);
  drawFantome(f);
  drawFantome(f1);
  drawFantome(f2);
  
  int y = 15 + (21 * 30);
  float angle;
  int ray = 15;
  //permet la creation des triangles jaunes en haut a gauche de la fenetre du jeu, 
  // representant les vies du pacman
  for(int i = 0 ; i < vie; i++)
  {
    int x = 20 + (i * 30);
    for(angle = 0.6f; angle < 1.8f * M_PI; angle += 0.03f)
    {
      GLubyte r = 250.0, g = 250.0, b = 0.0;
      drawLine(x, y, x + ray * cos(angle), y + ray * sin(angle), RGB(r, g, b));
    }
  }

  gl4dpScreenHasChanged();
  /* fonction permettant de raffraîchir l'ensemble de la fenêtre*/
  gl4dpUpdateScreen(NULL);
  /*MAJ on bouge tout le monde pour voir */
}