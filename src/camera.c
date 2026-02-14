typedef struct {
  float aspect_ratio;
  int image_width;
  int samples_per_pixel;
  int max_depth;
  // private
  int image_height;
  float pixel_samples_scale;
  Point3 center;
  Point3 pixel00_loc;
  Vec3 pixel_delta_u;
  Vec3 pixel_delta_v;
} Camera;

static void camera_initialize(Camera *c) {
  c->image_height = (int)(c->image_width / c->aspect_ratio);
  c->image_height = (c->image_height < 1) ? 1 : c->image_height;

  c->pixel_samples_scale = 1.0f / c->samples_per_pixel;
  c->center = (Point3){0, 0, 0};

  float focal_length = 1.0f;
  float viewport_height = 2.0f;
  float viewport_width = viewport_height * c->image_width / c->image_height;

  Vec3 viewport_u = {.x = viewport_width};
  Vec3 viewport_v = {.y = -viewport_height};

  c->pixel_delta_u = vec3_scale(viewport_u, 1.0f / c->image_width);
  c->pixel_delta_v = vec3_scale(viewport_v, 1.0f / c->image_height);

  Point3 viewport_mid_mid = vec3_sub(c->center, (Vec3){.z = focal_length});
  Point3 viewport_mid_left = vec3_sub(viewport_mid_mid, vec3_scale(viewport_u, 0.5f));
  Point3 viewport_top_left = vec3_sub(viewport_mid_left, vec3_scale(viewport_v, 0.5f));

  c->pixel00_loc = vec3_add(viewport_top_left, vec3_scale(vec3_add(c->pixel_delta_u, c->pixel_delta_v), 0.5f));
}

static Vec3 camera_sample_square(const Camera *c) {
  return (Vec3){random_float() - 0.5f, random_float() - 0.5f, 0.0f};
}

static Ray3 camera_get_ray(const Camera *c, int i, int j) {
  Vec3 offset = camera_sample_square(c);

  Vec3 pixel_x_offset = vec3_scale(c->pixel_delta_u, i + offset.x);
  Vec3 pixel_y_offset = vec3_scale(c->pixel_delta_v, j + offset.y);
  Point3 pixel_sample = vec3_add(vec3_add(c->pixel00_loc, pixel_x_offset), pixel_y_offset);

  Vec3 ray_direction = vec3_sub(pixel_sample, c->center);
  return (Ray3){.origin = c->center, .direction = ray_direction};
}

static Color3 camera_ray_color(const Camera *c, const Ray3 *ray, int depth, const Hittable *world) {
  if (depth <= 0) return BLACK;

  Hit hit;
  if (hittable_hit(world, ray, (Interval){0.001f, INFINITY}, &hit)) {
    Vec3 direction = vec3_random_on_hemisphere(hit.normal);
    Ray3 new_ray = {.origin = hit.p, .direction = direction};
    return vec3_scale(camera_ray_color(c, &new_ray, depth - 1, world), 0.5f);
  }

  Vec3 unit_direction = vec3_unit(ray->direction);
  float alpha = 0.5f * (unit_direction.y + 1.0f);
  return vec3_lerp(WHITE, SKY_BLUE, alpha);
}

static void camera_render(Camera *c, const Hittable *world) {
  camera_initialize(c);

  printf("P3\n%d %d\n255\n", c->image_width, c->image_height);

  for (int j = 0; j < c->image_height; j++) {
    fprintf(stderr, "\rScanlines remaining: %d ", (c->image_height - j));
    for (int i = 0; i < c->image_width; i++) {
      Color3 pixel_color = {0.0f, 0.0f, 0.0f};
      for (int sample = 0; sample < c->samples_per_pixel; sample++) {
        Ray3 ray = camera_get_ray(c, i, j);
        pixel_color = vec3_add(pixel_color, camera_ray_color(c, &ray, c->max_depth, world));
      }
      color3_write_line(vec3_scale(pixel_color, c->pixel_samples_scale), stdout);
    }
  }

  fprintf(stderr, "\rDone.                 \n");
}
