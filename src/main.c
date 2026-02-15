#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "util.c"
#include "vec3.c"
#include "point3.c"
#include "interval.c"
#include "color3.c"
#include "ray3.c"
#include "hit.c"
#include "sphere.c"
#include "hittable.c"
#include "hittable_list.c"
#include "lambertian.c"
#include "metal.c"
#include "dielectric.c"
#include "material.c"
#include "camera.c"

int main(void) {
  srand((unsigned int)time(NULL));

  HittableList list = {0};
  Hittable world = {.type = HITTABLE_LIST, .u.list = &list};

  float R = cosf(PI / 4.0f);

  Material material_left = {.type = MATERIAL_LAMBERTIAN, .u.lambertian = {.albedo = {0.0f, 0.0f, 1.0f}}};
  Material material_right = {.type = MATERIAL_LAMBERTIAN, .u.lambertian = {.albedo = {1.0f, 0.0f, 0.0f}}};

  hittable_list_add(&list, (Hittable){.type = HITTABLE_SPHERE, .u.sphere = {.center = {-R, 0.0f, -1.0f}, .radius = R, .material = &material_left}});
  hittable_list_add(&list, (Hittable){.type = HITTABLE_SPHERE, .u.sphere = {.center = {R, 0.0f, -1.0f}, .radius = R, .material = &material_right}});

  Camera camera = {.aspect_ratio = 16.0f / 9.0f, .image_width = 400, .samples_per_pixel = 10, .max_depth = 10, .vfov = 90.0f};
  camera_render(&camera, &world);
}
