#include <stdio.h>
#include <math.h>
#include "vector3f.c"
#include "point3f.c"
#include "color3f.c"
#include "ray3f.c"

int main(void) {
  float aspect_ratio = 16.0f / 9.0f;
  int image_width = 400;

  int image_height = (int)(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  float focal_length = 1.0f;
  float viewport_height = 2.0f;
  float viewport_width = viewport_height * image_width / image_height;
  Point3f camera_center = { 0, 0, 0 };

  Vector3f viewport_u = { .x = viewport_width };
  Vector3f viewport_v = { .y = -viewport_height };
  Vector3f viewport_half_u = vector3f_scale(&viewport_u, 0.5f);
  Vector3f viewport_half_v = vector3f_scale(&viewport_v, 0.5f);

  Vector3f pixel_delta_u = vector3f_scale(&viewport_u, 1.0f / image_width);
  Vector3f pixel_delta_v = vector3f_scale(&viewport_v, 1.0f / image_height);
  Vector3f pixel_delta_uv = vector3f_add(&pixel_delta_u, &pixel_delta_v);
  Vector3f pixel_delta_half_uv = vector3f_scale(&pixel_delta_uv, 0.5f);

  Point3f viewport_mid_mid = vector3f_subtract(&camera_center, &(Vector3f){ .z = focal_length });
  Point3f viewport_mid_left = vector3f_subtract(&viewport_mid_mid, &viewport_half_u);
  Point3f viewport_top_left = vector3f_subtract(&viewport_mid_left, &viewport_half_v);
  Point3f pixel00_loc = vector3f_add(&viewport_top_left, &pixel_delta_half_uv);

  printf("P3\n%d %d\n255\n", image_width, image_height);

  for (int j = 0; j < image_height; j++) {
    fprintf(stderr, "\rScanlines remaining: %d ", (image_height - j));
    for (int i = 0; i < image_width; i++) {
      Vector3f pixel_x_offset = vector3f_scale(&pixel_delta_u, i);
      Vector3f pixel_y_offset = vector3f_scale(&pixel_delta_v, j);
      Point3f pixel_center = vector3f_add(&pixel00_loc, &pixel_x_offset);
      pixel_center = vector3f_add(&pixel_center, &pixel_y_offset);

      Vector3f ray_direction = vector3f_subtract(&pixel_center, &camera_center);
      Ray3f r = { .origin = camera_center, .direction = ray_direction };

      Color3f pixel_color = ray3f_color(&r);
      color3f_write_line(&pixel_color, stdout);
    }
  }

  fprintf(stderr, "\rDone.                 \n");
  return 0;
}
