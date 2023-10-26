#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

typedef struct {
  int x, y;
  unsigned char r, g, b;
} Vec2;

#define WIDTH 800
#define HEIGHT 600
#define NPOINTS 50
Vec2 points[NPOINTS];

int main(void) {
  srand(time(NULL));
  for (int i = 0; i < NPOINTS; ++i) {
    points[i].x = rand() % WIDTH;
    points[i].y = rand() % HEIGHT;
    points[i].r = rand() % 256;
    points[i].g = rand() % 256;
    points[i].b = rand() % 256;
  }
  unsigned char *image = malloc(WIDTH * HEIGHT * 3);
  for (int y = 0; y < HEIGHT; ++y) {
    for (int x = 0; x < WIDTH; ++x) {
      int min_dist_i = 0;
      uint64_t min_dist_sqr = INT_MAX;
      for (int i = 0; i < NPOINTS; ++i) {
        uint64_t dist_sqr = (x-points[i].x)*(x-points[i].x) + (y-points[i].y)*(y-points[i].y);
        if (dist_sqr < min_dist_sqr) {
          min_dist_sqr = dist_sqr;
          min_dist_i = i;
        }
      }
      image[y * WIDTH * 3 + x * 3 + 0] = points[min_dist_i].r;
      image[y * WIDTH * 3 + x * 3 + 1] = points[min_dist_i].g;
      image[y * WIDTH * 3 + x * 3 + 2] = points[min_dist_i].b;
    }
  }
  stbi_write_png("out.png", WIDTH, HEIGHT, 3, image, WIDTH * 3);
  free(image);
  return 0;
}
