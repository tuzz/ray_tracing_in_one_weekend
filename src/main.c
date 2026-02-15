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
#include "material.c"
#include "camera.c"

int main(void) {
  srand((unsigned int)time(NULL));

  Material material_ground = {.type = MATERIAL_LAMBERTIAN, .u.lambertian = {.albedo = {0.8f, 0.8f, 0.0f}}};
  Material material_center = {.type = MATERIAL_LAMBERTIAN, .u.lambertian = {.albedo = {0.1f, 0.2f, 0.5f}}};
  Material material_left = {.type = MATERIAL_METAL, .u.metal = {.albedo = {0.8f, 0.8f, 0.8f}, .fuzz = 0.3f}};
  Material material_right = {.type = MATERIAL_METAL, .u.metal = {.albedo = {0.8f, 0.6f, 0.2f}, .fuzz = 1.0f}};

  HittableList list = {0};
  Hittable world = {.type = HITTABLE_LIST, .u.list = &list};

  hittable_list_add(&list, (Hittable){.type = HITTABLE_SPHERE, .u.sphere = {.center = {0.0f, -100.5f, -1.0f}, .radius = 100.0f, .material = &material_ground}});
  hittable_list_add(&list, (Hittable){.type = HITTABLE_SPHERE, .u.sphere = {.center = {0.0f, 0.0f, -1.2f}, .radius = 0.5f, .material = &material_center}});
  hittable_list_add(&list, (Hittable){.type = HITTABLE_SPHERE, .u.sphere = {.center = {-1.0f, 0.0f, -1.0f}, .radius = 0.5f, .material = &material_left}});
  hittable_list_add(&list, (Hittable){.type = HITTABLE_SPHERE, .u.sphere = {.center = {1.0f, 0.0f, -1.0f}, .radius = 0.5f, .material = &material_right}});

  Camera camera = {.aspect_ratio = 16.0f / 9.0f, .image_width = 400, .samples_per_pixel = 10, .max_depth = 10};
  camera_render(&camera, &world);
}
