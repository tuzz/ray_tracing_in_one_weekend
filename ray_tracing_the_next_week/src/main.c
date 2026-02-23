#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "util.c"
#include "vec3.c"
#include "point3.c"
#include "interval.c"
#include "color3.c"
#include "ray3.c"
#include "hit.c"
#include "aabb.c"
#include "sphere.c"
#include "solid_color.c"
#include "texture.c"
#include "checker_texture.c"
#include "hittable.c"
#include "hittable_list.c"
#include "lambertian.c"
#include "metal.c"
#include "dielectric.c"
#include "material.c"
#include "camera.c"
#include "bvh.c"

int main(void) {
  HittableList list = hittable_list_new();

  Texture dark = {.type = TEXTURE_SOLID_COLOR, .u.solid_color.albedo = {{0.2f, 0.3f, 0.1f}}};
  Texture light = {.type = TEXTURE_SOLID_COLOR, .u.solid_color.albedo = {{0.9f, 0.9f, 0.9f}}};
  CheckerTexture check = {.inv_scale = 1.0f / 0.32f, .even = &dark, .odd = &light};
  Texture checker = {.type = TEXTURE_CHECKER, .u.checker_texture = &check };

  Material ground_material = {.type = MATERIAL_LAMBERTIAN, .u.lambertian.tex = &checker};
  hittable_list_add(&list, (Hittable){.type = HITTABLE_SPHERE, .u.sphere = sphere_new((Ray3){.origin = {{0.0f, -1000.0f, 0.0f}}}, 1000.0f, &ground_material)});

  Texture textures[500] = {0};
  int texture_count = 0;

  Material materials[500] = {0};
  int material_count = 0;

  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      float choose_mat = random_float();
      Point3 center = {{a + 0.9f * random_float(), 0.2f, b + 0.9f * random_float()}};

      if (vec3_length(vec3_sub(center, (Point3){{4.0f, 0.2f, 0.0f}})) > 0.9f) {
        Material *sphere_material = &materials[material_count++];

        if (choose_mat < 0.8f) {
          // diffuse
          Texture *sphere_texture = &textures[texture_count++];
          *sphere_texture = (Texture){.type = TEXTURE_SOLID_COLOR, .u.solid_color.albedo = vec3_mul(vec3_random(), vec3_random()) };
          *sphere_material = (Material){.type = MATERIAL_LAMBERTIAN, .u.lambertian.tex = sphere_texture};
          Ray3 center_ray = (Ray3){.origin = center, .direction.coord.y = random_between(0.0f, 0.5f)};
          hittable_list_add(&list, (Hittable){.type = HITTABLE_SPHERE, .u.sphere = sphere_new(center_ray, 0.2f, sphere_material)});
        } else if (choose_mat < 0.95f) {
          // metal
          Color3 albedo = vec3_random_between(0.5f, 1.0f);
          float fuzz = random_between(0.0, 0.5f);
          *sphere_material = (Material){.type = MATERIAL_METAL, .u.metal = {.albedo = albedo, .fuzz = fuzz}};
          hittable_list_add(&list, (Hittable){.type = HITTABLE_SPHERE, .u.sphere = sphere_new((Ray3){.origin = center}, 0.2f, sphere_material)});
        } else {
          // glass
          *sphere_material = (Material){.type = MATERIAL_DIELECTRIC, .u.dielectric.refaction_index = 1.5f};
          hittable_list_add(&list, (Hittable){.type = HITTABLE_SPHERE, .u.sphere = sphere_new((Ray3){.origin = center}, 0.2f, sphere_material)});
        }
      }
    }
  }

  Material material1 = {.type = MATERIAL_DIELECTRIC, .u.dielectric.refaction_index = 1.5f};
  hittable_list_add(&list, (Hittable){.type = HITTABLE_SPHERE, .u.sphere = sphere_new((Ray3){.origin = {{0.0f, 1.0f, 0.0f}}}, 1.0f, &material1)});

  Texture tex = {.type = TEXTURE_SOLID_COLOR, .u.solid_color.albedo = {{0.4f, 0.2f, 0.1f}}};
  Material material2 = {.type = MATERIAL_LAMBERTIAN, .u.lambertian.tex = &tex};
  hittable_list_add(&list, (Hittable){.type = HITTABLE_SPHERE, .u.sphere = sphere_new((Ray3){.origin = {{-4.0f, 1.0f, 0.0f}}}, 1.0f, &material2)});

  Material material3 = {.type = MATERIAL_METAL, .u.metal = {.albedo = {{0.7f, 0.6f, 0.5f}}, .fuzz = 0.0f}};
  hittable_list_add(&list, (Hittable){.type = HITTABLE_SPHERE, .u.sphere = sphere_new((Ray3){.origin = {{4.0f, 1.0f, 0.0f}}}, 1.0f, &material3)});

  BVH bvh = {0};
  Hittable *world = bvh_node(&bvh, list.items, 0, list.length);

  Camera camera = {0};
  camera.aspect_ratio = 16.0f / 9.0f;
  camera.image_width = 400;
  camera.samples_per_pixel = 100;
  camera.max_depth = 50;

  camera.vfov = 20.0f;
  camera.lookfrom = (Point3){{13.0f, 2.0f, 3.0f}};
  camera.lookat = (Point3){{0.0f, 0.0f, 0.0f}};
  camera.vup = (Point3){{0.0f, 1.0f, 0.0f}};

  camera.defocus_angle = 0.6f;
  camera.focus_dist = 10.0f;

  camera_render(&camera, world);
}
