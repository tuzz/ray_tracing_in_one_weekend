#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "vec3.c"
#include "point3.c"
#include "color3.c"
#include "ray3.c"
#include "hit.c"
#include "hittable.c"
#include "sphere.c"

static Color3 ray3_color(const Ray3 *r, const Hittable *hittable) {
  Hit hit;
  if (hittable->hit(hittable, r, 0.0f, 999.0f, &hit)) {
    return vec3_scale((Vec3){hit.normal.x + 1.0f, hit.normal.y + 1.0f, hit.normal.z + 1.0f}, 0.5f);
  }

  Vec3 unit_direction = vec3_unit(r->direction);
  float alpha = 0.5f * (unit_direction.y + 1.0f);

  Color3 white = {1.0f, 1.0f, 1.0f};
  Color3 sky_blue = {0.5f, 0.7f, 1.0f};

  return vec3_lerp(white, sky_blue, alpha);
}

int main(void) {
  float aspect_ratio = 16.0f / 9.0f;
  int image_width = 400;

  int image_height = (int)(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  float focal_length = 1.0f;
  float viewport_height = 2.0f;
  float viewport_width = viewport_height * image_width / image_height;
  Point3 camera_center = {0, 0, 0};

  Vec3 viewport_u = {.x = viewport_width};
  Vec3 viewport_v = {.y = -viewport_height};

  Vec3 pixel_delta_u = vec3_scale(viewport_u, 1.0f / image_width);
  Vec3 pixel_delta_v = vec3_scale(viewport_v, 1.0f / image_height);

  Point3 viewport_mid_mid = vec3_sub(camera_center, (Vec3){.z = focal_length});
  Point3 viewport_mid_left = vec3_sub(viewport_mid_mid, vec3_scale(viewport_u, 0.5f));
  Point3 viewport_top_left = vec3_sub(viewport_mid_left, vec3_scale(viewport_v, 0.5f));
  Point3 pixel00_loc = vec3_add(viewport_top_left, vec3_scale(vec3_add(pixel_delta_u, pixel_delta_v), 0.5f));

  printf("P3\n%d %d\n255\n", image_width, image_height);
  Sphere sphere = {.base.hit = sphere_hit, .center = {0.0f, 0.0f, -1.0f}, .radius = 0.5};

  for (int j = 0; j < image_height; j++) {
    fprintf(stderr, "\rScanlines remaining: %d ", (image_height - j));
    for (int i = 0; i < image_width; i++) {
      Vec3 pixel_x_offset = vec3_scale(pixel_delta_u, i);
      Vec3 pixel_y_offset = vec3_scale(pixel_delta_v, j);
      Point3 pixel_center = vec3_add(pixel00_loc, pixel_x_offset);
      pixel_center = vec3_add(pixel_center, pixel_y_offset);

      Vec3 ray_direction = vec3_sub(pixel_center, camera_center);
      Ray3 r = {.origin = camera_center, .direction = ray_direction};

      Color3 pixel_color = ray3_color(&r, (Hittable *)&sphere);
      color3_write_line(pixel_color, stdout);
    }
  }

  fprintf(stderr, "\rDone.                 \n");
  return 0;
}
