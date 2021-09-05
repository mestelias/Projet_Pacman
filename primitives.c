/*
 * ATTENTION CE CODE EST LE RÉSULTAT OBTENU SUITE À CE QUI A ÉTÉ FAIT
 * EN COURS, IL A ÉTÉ LÉGÈREMENT CORRIGÉ POUR ÊTRE FONCTIONNEL MAIS IL
 * N'Y A AUCUNE GARANTIE QUE TOUTES LES SITUATIONS AIENT ÉTÉ
 * CORRIGÉES.
 *
 * POUR INFORMATION, LÀ OÙ VOUS TROUVEREZ "MAJ" CORRESPOND À DES
 * LIGNES OÙ JE SUIS INTERVENU EN DEHORS DE LA SÉANCE DE COURS.
*/

#include "primitives.h"
#include <assert.h>

static void abscisses(vertex_t * p0, vertex_t * p1, vertex_t * absc, int replace);
static void drawHLine(vertex_t * vG, vertex_t * vD, int y);

//fonction qui permet de creer un carre ce qui nous permettra de creer les murs du labyrinthe
extern void mur(int x0, int y0) 
{
  int x = x0 * 30, y = y0 * 30;
  triangle_t t = 
  {  /* p[3] */
		{ /* x, y, color, texCoord */
			{ x, y, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 0.0f}}, /* p[0] */
			{ x, y + 30, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 10.0f}}, /* p[1] */
			{ x + 30, y, {0.0f, 0.0f, 1.0f, 1.0f}, {10.0f, 10.0f}}  /* p[2] */
		} 
  };
  triangle_t z = 
  { /* p[3] */
		{ /* x, y, color, texCoord */
		  { x + 30, y + 30, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 0.0f}}, /* p[0] */
		  { x, y + 30, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 10.0f}}, /* p[1] */
		  { x + 30, y, {0.0f, 0.0f, 1.0f, 1.0f}, {10.0f, 10.0f}}  /* p[2] */
		} 
  };
  fillTriangle(&z);
  fillTriangle(&t);
}

//fonction qui permet de creer la nourriture du pacman
void nourriture(int x0, int y0)
{
  int x = x0 * 30, y = y0 * 30;
  triangle_t v = 
  {
    {
      { x + 10, y + 10, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, /* p[0] */
		  { x + 15 , y + 20, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 10.0f}}, /* p[1] */
		  { x + 20, y + 10, {1.0f, 1.0f, 0.0f, 1.0f}, {10.0f, 10.0f}}  /* p[2] */ 
    }
  };
  fillTriangle(&v);
}

//fonction qui permet de creer la nourriture magique du pacman, celle qui lui donne des pouvoirs
void nourritureMagique(int x0, int y0)
{
  int x = x0 * 30, y = y0 * 30;

  vec4 v = {(rand()%256)/(float)255,(rand()%256)/(float)255,(rand()%256)/(float)255,1.0f};

  triangle_t p = 
  {
    {
      { x + 10, y + 10, v, {0.0f, 0.0f}}, /* p[0] */
		  { x + 15 , y + 25, v, {0.0f, 10.0f}}, /* p[1] */
		  { x + 20, y + 10, v, {10.0f, 10.0f}}  /* p[2] */ 
    }
  };
  triangle_t p2 = 
  {
    {
      { x + 10, y + 15, v, {0.0f, 0.0f}}, /* p[0] */
		  { x + 15 , y + 1, v, {0.0f, 10.0f}}, /* p[1] */
		  { x + 20, y + 15, v, {10.0f, 10.0f}}  /* p[2] */ 
    }
  };
  fillTriangle(&p);
  fillTriangle(&p2);  
}

void fillTriangle(triangle_t * t) {
  int bas, median, haut, n, signe, i;
  vertex_t * aG = NULL, * aD = NULL;
  if(t->p[0].y < t->p[1].y) {
    if(t->p[0].y < t->p[2].y) {
      bas = 0;
      if(t->p[1].y < t->p[2].y) {
	median = 1;
	haut = 2;
      } else {
	median = 2;
	haut = 1; 
      }
    } else {
      bas = 2;
      /*MAJ déjà faux, ne sert à rien */
      /* if(t->p[1].y < t->p[0].y) { */
      /* 	median = 1; */
      /* 	haut = 0; */
      /* } else { */
	median = 0;
	haut = 1;
      /* } */
    }
  } else { /* p0 au dessus de p1 */
    if(t->p[1].y < t->p[2].y) {
      bas = 1;
      if(t->p[0].y < t->p[2].y) {
	median = 0;
	haut = 2;
      } else {
	median = 2;
	haut = 0;
      }
    } else {
      bas = 2;
      /*MAJ déjà vrai, ne sert à rien */
      /* if(t->p[1].y < t->p[0].y) { */
	median = 1;
	haut = 0;
      /* } else { */
      /* 	median = 0; */
      /* 	haut = 1; */
      /* } */
    }
  }
  n = t->p[haut].y - t->p[bas].y + 1;
  /* printf("%d\n", n); */
  aG = malloc(n * sizeof *aG);
  assert(aG);
  aD = malloc(n * sizeof *aD);
  assert(aD);
  /* est-ce que Pm est à gauche (+) ou à droite (-) de la droite (Pb->Ph) ? */
  /*MAJ, idée TODO?, un produit vectoriel pourrait s'avérer mieux */
  if(t->p[haut].x == t->p[bas].x /*MAJ*/ || t->p[haut].y == t->p[bas].y) {
    /* eq de la droite x = t->p[haut].x; MAJ ou y = t->p[haut].y; */
    signe = (t->p[median].x > t->p[haut].x) ? -1 : 1;
  } else {
    /* eq ax + y + c = 0 */
    float a, c, x;
    a = (t->p[haut].y - t->p[bas].y) / (float)(t->p[bas].x - t->p[haut].x);
    c = -a * t->p[haut].x - t->p[haut].y;
    /*MAJ on trouve le x sur la droite au même y que le median et on compare */
    x = -(c + t->p[median].y) / a;
    signe = (t->p[median].x >= x) ? -1 : 1;
  }
  /* printf("signe %d\n", signe); */
  if(signe < 0) { /* aG reçoit Ph->Pb, et aD reçoit Ph->Pm puis Pm vers Pb */
    abscisses(&(t->p[haut]), &(t->p[bas]), aG, 1);
    abscisses(&(t->p[haut]), &(t->p[median]), aD, 1);
    abscisses(&(t->p[median]), &(t->p[bas]), &aD[t->p[haut].y - t->p[median].y], 0);
  } else { /* aG reçoit Ph->Pm puis Pm vers Pb, et aD reçoit Ph->Pb */
    abscisses(&(t->p[haut]), &(t->p[bas]), aD, 1);
    abscisses(&(t->p[haut]), &(t->p[median]), aG, 1);
    abscisses(&(t->p[median]), &(t->p[bas]), &aG[t->p[haut].y - t->p[median].y], 0);
  }
  /*MAJ print pouvant être utile*/
  /* printf("signe: %d, haut = %d (%d, %d), median = %d (%d, %d), bas = %d (%d, %d)\n", signe, */
  /* 	 haut, t->p[haut].x, t->p[haut].y, median, t->p[median].x, t->p[median].y, bas, t->p[bas].x, t->p[bas].y); */
  for(i = 0; i < n; ++i) {
    /*MAJ test évitant les y en dehors de l'image*/
    if(t->p[haut].y - i >= 0 && t->p[haut].y - i < gl4dpGetHeight())
      drawHLine(&aG[i], &aD[i], t->p[haut].y - i);
    /*MAJ assertion au cas où PB*/
    /* assert(aG[i].x <= aD[i].x); */
  }
  free(aG);
  free(aD);
}

void drawLine(int x0, int y0, int x1, int y1, GLuint color) {
  int u = x1 - x0, v = y1 - y0, pasX = u < 0 ? -1 : 1, pasY = v < 0 ? -1 : 1;
  int w = gl4dpGetWidth();
  GLuint * image = gl4dpGetPixels();
  u = abs(u); v = abs(v);
  if(u > v) { // 1er octan
    int objX = (u + 1) * pasX;
    int delta = u - 2 * v, incH = -2 * v, incO = 2 * u - 2 * v;
    for (int x = 0, y = 0; x != objX; x += pasX) {
      if(IN_SCREEN(x + x0, y0 + y))
	image[(y0 + y) * w + x + x0] = color;
      if(delta < 0) {
	y += pasY;
	delta += incO;
      } else
	delta += incH;
    }
  } else { // 2eme octan
    int objY = (v + 1) * pasY;
    int delta = v - 2 * u, incH = -2 * u, incO = 2 * v - 2 * u;
    for (int x = 0, y = 0; y != objY; y += pasY) {
      if(IN_SCREEN(x + x0, y0 + y))
	image[(y0 + y) * w + x + x0] = color;
      if(delta < 0) {
	x += pasX;
	delta += incO;
      } else
	delta += incH;
    }
  }
}

void abscisses(vertex_t * p0, vertex_t * p1, vertex_t * absc, int replace) {
  int u = p1->x - p0->x, v = p1->y - p0->y, pasX = u < 0 ? -1 : 1, pasY = v < 0 ? -1 : 1, i;
  float dmax = sqrt(u * u + v * v), d, f0, f1;
  u = abs(u); v = abs(v);
  if(u > v) { // 1er octan
    if(replace) {
      int objX = (u + 1) * pasX;
      int delta = u - 2 * v, incH = -2 * v, incO = 2 * u - 2 * v;
      for (int x = 0, y = 0, k = 0; x != objX; x += pasX) {
	d = sqrt(x * x + y * y);
	f1 = d / dmax; f0 = 1.0f - f1;
	absc[k].x = x + p0->x;
	for(i = 0; i < 4; ++i)
	  ((float *)&(absc[k].color))[i] = f0 * ((float *)&(p0->color))[i] + f1 * ((float *)&(p1->color))[i];
	for(i = 0; i < 2; ++i)
	  ((float *)&(absc[k].texCoord))[i] = f0 * ((float *)&(p0->texCoord))[i] + f1 * ((float *)&(p1->texCoord))[i];
	if(delta < 0) {
	  ++k;
	  y += pasY;
	  delta += incO;
	} else
	  delta += incH;
      }
    } else {
      int objX = (u + 1) * pasX;
      int delta = u - 2 * v, incH = -2 * v, incO = 2 * u - 2 * v;
      for (int x = 0, y = 0, k = 0, done = 0; x != objX; x += pasX) {
	if(!done) {
	  d = sqrt(x * x + y * y);
	  f1 = d / dmax; f0 = 1.0f - f1;
	  absc[k].x = x + p0->x;
	  for(i = 0; i < 4; ++i)
	    ((float *)&(absc[k].color))[i] = f0 * ((float *)&(p0->color))[i] + f1 * ((float *)&(p1->color))[i];
	  for(i = 0; i < 2; ++i)
	    ((float *)&(absc[k].texCoord))[i] = f0 * ((float *)&(p0->texCoord))[i] + f1 * ((float *)&(p1->texCoord))[i];
	  done = 1;
	}
	if(delta < 0) {
	  ++k;
	  done = 0;
	  y += pasY;
	  delta += incO;
	} else
	  delta += incH;
      }
    }
  } else { // 2eme octan
    int objY = (v + 1) * pasY;
    int delta = v - 2 * u, incH = -2 * u, incO = 2 * v - 2 * u;
    for (int x = 0, y = 0, k = 0; y != objY; y += pasY) {
      d = sqrt(x * x + y * y);
      f1 = d / dmax; f0 = 1.0f - f1;
      absc[k].x = x + p0->x;
      for(i = 0; i < 4; ++i)
      	((float *)&(absc[k].color))[i] = f0 * ((float *)&(p0->color))[i] + f1 * ((float *)&(p1->color))[i];
      for(i = 0; i < 2; ++i)
      	((float *)&(absc[k].texCoord))[i] = f0 * ((float *)&(p0->texCoord))[i] + f1 * ((float *)&(p1->texCoord))[i];
      ++k;
      if(delta < 0) {
	x += pasX;
	delta += incO;
      } else
	delta += incH;
    }
  }
}

#define TW 2
#define TH 2

void drawHLine(vertex_t * vG, vertex_t * vD, int y) {
  int w = gl4dpGetWidth(), x, yw = y * w, i;
  GLuint * image = gl4dpGetPixels();
  float p, dp = 1.0f / (vD->x - vG->x);
  GLubyte c[4];
  //vec2 texCoord;
  /* il reste d'autres tests, par exemple y est au dessus ou en dessous de l'écran */
  for(x = vG->x, p = 0.0f; x <= vD->x; ++x, p += dp)
   { if(IN_SCREEN(x, y)) {
      for(i = 0; i < 4; ++i)
	  c[i] = ((float *)&(vG->color))[i]*255.9;
      image[yw + x] = RGBA(c[0], c[1], c[2], c[3]);
    }
}}