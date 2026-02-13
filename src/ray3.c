typedef struct {
  Point3 origin;
  Vec3 direction;
} Ray3;

static Point3 ray3_at(Ray3 self, float t) {
  return vec3_add(self.origin, vec3_scale(self.direction, t));
}

static float ray3_hit_sphere(Ray3 self, Point3 center, float radius) {
  Vec3 oc = vec3_subtract(center, self.origin);

  float a = vec3_length_squared(self.direction);
  float h = vec3_dot(self.direction, oc);
  float c = vec3_length_squared(oc) - radius * radius;
  float discriminant = h * h - a * c;

  if (discriminant < 0) {
    return -1.0f;
  } else {
    return (h - sqrtf(discriminant)) / a;
  }
}

static Color3 ray3_color(Ray3 self) {
  Point3 sphere_center = { 0.0f, 0.0f, -1.0f };
  float t = ray3_hit_sphere(self, sphere_center, 0.5);

  if (t > 0.0f) {
    Point3 sphere_point = ray3_at(self, t);
    Vec3 normal = vec3_unit(vec3_subtract(sphere_point, sphere_center));
    return vec3_scale((Vec3){ normal.x + 1.0f, normal.y + 1.0f, normal.z + 1.0f }, 0.5f);
  }

  Vec3 unit_direction = vec3_unit(self.direction);
  float alpha = 0.5f * (unit_direction.y + 1.0f);

  Color3 white = { 1.0f, 1.0f, 1.0f };
  Color3 sky_blue = { 0.5f, 0.7f, 1.0f };

  return vec3_lerp(white, sky_blue, alpha);
}
