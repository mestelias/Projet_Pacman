#ifndef PRIMITIVES_H_SEEN
#  define PRIMITIVES_H_SEEN

#  include <GL4D/gl4dp.h>

#  ifdef __cplusplus
extern "C" {
#  endif
  
  typedef struct vec4 vec4;
  typedef struct vec2 vec2;
  typedef struct vertex_t vertex_t;
  typedef struct triangle_t triangle_t;
  
  struct vec4 {
    float x /* r */, y/* g */, z /* b */, w /* a */;
  };

  struct vec2 {
    float x /* s */, y /* t */;
  };

  struct vertex_t {
    int x, y;
    vec4 color;
    vec2 texCoord; 
    /* OBJECTIF vec4 coord; vec4 color; vec2 texCoord; vec4 normal; */
  };

  struct triangle_t {
    vertex_t p[3];
  };
  
  extern void fillTriangle(triangle_t * t);
  extern void drawLine(int x0, int y0, int x1, int y1, GLuint color);
  extern void mur(int x0, int y0);
  extern void nourriture(int x0, int y0);
  extern void nourritureMagique(int x0, int y0);

#  ifdef __cplusplus
}
#  endif


#endif
