typedef struct {
  float aspect_ratio;
  int image_width;
  int image_height;
  Point3 center;
  Point3 pixel00_loc;
  Vec3 pixel_delta_u;
  Vec3 pixel_delta_v;
} Camera;

static void camera_initialize(Camera *c) {
  c->image_height = (int)(c->image_width / c->aspect_ratio);
  c->image_height = (c->image_height < 1) ? 1 : c->image_height;

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

static Color3 camera_ray_color(const Camera *c, const Ray3 *ray, const Hittable *world) {
  Hit hit;

  if (hittable_hit(world, ray, (Interval){0.0f, INFINITY}, &hit)) {
    return vec3_scale(vec3_add(hit.normal, (Vec3){1.0f, 1.0f, 1.0f}), 0.5f);
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
      Vec3 pixel_x_offset = vec3_scale(c->pixel_delta_u, i);
      Vec3 pixel_y_offset = vec3_scale(c->pixel_delta_v, j);

      Point3 pixel_center = vec3_add(c->pixel00_loc, pixel_x_offset);
      pixel_center = vec3_add(pixel_center, pixel_y_offset);

      Vec3 ray_direction = vec3_sub(pixel_center, c->center);
      Ray3 ray = {.origin = c->center, .direction = ray_direction};

      Color3 pixel_color = camera_ray_color(c, &ray, world);
      color3_write_line(pixel_color, stdout);
    }
  }

  fprintf(stderr, "\rDone.                 \n");
}
