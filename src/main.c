#include <stdio.h>
#include <math.h>
#include "vector3f.c"
#include "point3f.c"
#include "color3f.c"

int main(void) {
  int image_width = 256;
  int image_height = 256;

  printf("P3\n%d %d\n255\n", image_width, image_height);

  for (int j = 0; j < image_height; j++) {
    fprintf(stderr, "\rScanlines remaining: %d ", (image_height - j));
    for (int i = 0; i < image_width; i++) {
      Vector3f pixel_color = { (float)i / (image_width - 1), (float)j / (image_height - 1), 0 };
      color3f_write_line(&pixel_color, stdout);
    }
  }

  fprintf(stderr, "\rDone.                 \n");
  return 0;
}
