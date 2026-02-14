#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "util.c"
#include "vec3.c"
#include "point3.c"
#include "color3.c"
#include "interval.c"
#include "ray3.c"
#include "hit.c"
#include "sphere.c"
#include "hittable.c"
#include "hittable_list.c"
#include "camera.c"

int main(void) {
  HittableList list = {0};
  Hittable world = {.type = HITTABLE_LIST, .u.list = &list};

  hittable_list_add(&list, (Hittable){.type = HITTABLE_SPHERE, .u.sphere = {.center = {0.0f, 0.0f, -1.0f}, .radius = 0.5f}});
  hittable_list_add(&list, (Hittable){.type = HITTABLE_SPHERE, .u.sphere = {.center = {0.0f, -100.5f, -1.0f}, .radius = 100.0f}});

  Camera camera = {.aspect_ratio = 16.0f / 9.0f, .image_width = 400};
  camera_render(&camera, &world);
}
