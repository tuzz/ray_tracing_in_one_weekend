typedef struct {
  float aspect_ratio;
  int image_width;
  int samples_per_pixel;
  int max_depth;
  Color3 background;
  float vfov;
  Point3 lookfrom;
  Point3 lookat;
  Vec3 vup;
  float defocus_angle;
  float focus_dist;
  // private
  int image_height;
  float pixel_samples_scale;
  Point3 center;
  Point3 pixel00_loc;
  Vec3 pixel_delta_u;
  Vec3 pixel_delta_v;
  Vec3 u, v, w;
  Vec3 defocus_disk_u;
  Vec3 defocus_disk_v;
} Camera;

static void camera_initialize(Camera *c) {
  c->image_height = (int)(c->image_width / c->aspect_ratio);
  c->image_height = (c->image_height < 1) ? 1 : c->image_height;

  c->pixel_samples_scale = 1.0f / c->samples_per_pixel;
  c->center = c->lookfrom;

  float theta = degrees_to_radians(c->vfov);
  float h = tanf(theta / 2.0f);
  float viewport_height = 2.0f * h * c->focus_dist;
  float viewport_width = viewport_height * c->image_width / c->image_height;

  c->w = vec3_unit(vec3_sub(c->lookfrom, c->lookat));
  c->u = vec3_unit(vec3_cross(c->vup, c->w));
  c->v = vec3_cross(c->w, c->u);

  Vec3 viewport_u = vec3_scale(c->u, viewport_width);
  Vec3 viewport_v = vec3_scale(c->v, -viewport_height);

  c->pixel_delta_u = vec3_scale(viewport_u, 1.0f / c->image_width);
  c->pixel_delta_v = vec3_scale(viewport_v, 1.0f / c->image_height);

  Point3 viewport_mid_mid = vec3_sub(c->center, vec3_scale(c->w, c->focus_dist));
  Point3 viewport_mid_left = vec3_sub(viewport_mid_mid, vec3_scale(viewport_u, 0.5f));
  Point3 viewport_top_left = vec3_sub(viewport_mid_left, vec3_scale(viewport_v, 0.5f));
  c->pixel00_loc = vec3_add(viewport_top_left, vec3_scale(vec3_add(c->pixel_delta_u, c->pixel_delta_v), 0.5f));

  float defocus_radius = c->focus_dist * tanf(degrees_to_radians(c->defocus_angle / 2.0f));
  c->defocus_disk_u = vec3_scale(c->u, defocus_radius);
  c->defocus_disk_v = vec3_scale(c->v, defocus_radius);
}

static Vec3 camera_sample_square(const Camera *c) {
  return (Vec3){{random_float() - 0.5f, random_float() - 0.5f, 0.0f}};
}

static Point3 camera_defocus_disk_sample(const Camera *c) {
  Vec3 p = vec3_random_in_unit_disk();
  Vec3 right_offset = vec3_scale(c->defocus_disk_u, p.coord.x);
  Vec3 up_offset = vec3_scale(c->defocus_disk_v, p.coord.y);
  return vec3_add(c->center, vec3_add(right_offset, up_offset));
}

static Ray3 camera_get_ray(const Camera *c, int i, int j) {
  Vec3 offset = camera_sample_square(c);

  Vec3 pixel_x_offset = vec3_scale(c->pixel_delta_u, i + offset.coord.x);
  Vec3 pixel_y_offset = vec3_scale(c->pixel_delta_v, j + offset.coord.y);
  Point3 pixel_sample = vec3_add(vec3_add(c->pixel00_loc, pixel_x_offset), pixel_y_offset);

  Point3 ray_origin = c->defocus_angle <= 0.0f ? c->center : camera_defocus_disk_sample(c);
  Vec3 ray_direction = vec3_sub(pixel_sample, ray_origin);
  float ray_time = random_float();

  return (Ray3){.origin = ray_origin, .direction = ray_direction, .time = ray_time};
}

static Color3 camera_ray_color(const Camera *c, const Ray3 *ray, int depth, const Hittable *world) {
  if (depth <= 0) return BLACK;

  Hit hit;
  if (!hittable_hit(world, ray, (Interval){0.001f, FLT_MAX}, &hit))
    return c->background;

  Ray3 scattered;
  Color3 attenuation;
  Color3 color_from_emission = material_emitted(hit.material, hit.u, hit.v, hit.p);

  if (!material_scatter(hit.material, ray, &hit, &attenuation, &scattered))
    return color_from_emission;

  Color3 color_from_scatter = vec3_mul(attenuation, camera_ray_color(c, &scattered, depth - 1, world));
  return vec3_add(color_from_emission, color_from_scatter);
}

static void camera_render(Camera *c, const Hittable *world) {
  camera_initialize(c);

  printf("P3\n%d %d\n255\n", c->image_width, c->image_height);

  for (int j = 0; j < c->image_height; j++) {
    fprintf(stderr, "\rScanlines remaining: %d ", (c->image_height - j));
    for (int i = 0; i < c->image_width; i++) {
      Color3 pixel_color = {{0.0f, 0.0f, 0.0f}};
      for (int sample = 0; sample < c->samples_per_pixel; sample++) {
        Ray3 ray = camera_get_ray(c, i, j);
        pixel_color = vec3_add(pixel_color, camera_ray_color(c, &ray, c->max_depth, world));
      }
      color3_write_line(vec3_scale(pixel_color, c->pixel_samples_scale), stdout);
    }
  }

  fprintf(stderr, "\rDone.                 \n");
}
