typedef struct {
  Point3 origin;
  Vec3 direction;
} Ray3;

static Point3 ray3_at(Ray3 self, float t) {
  return vec3_add(self.origin, vec3_scale(self.direction, t));
}

static bool ray3_hit_sphere(Ray3 self, Point3 center, float radius) {
  Vec3 oc = vec3_subtract(center, self.origin);

  float a = vec3_dot(self.direction, self.direction);
  float b = -2.0f * vec3_dot(self.direction, oc);
  float c = vec3_dot(oc, oc) - radius * radius;

  float discriminant = b * b - 4.0f * a * c;
  return discriminant >= 0.0f;
}

static Color3 ray3_color(Ray3 self) {
  if (ray3_hit_sphere(self, (Point3){ 0.0f, 0.0f, -1.0f }, 0.5)) {
    return (Color3){ 1.0f, 0.0f, 0.0f };
  }

  Vec3 unit_direction = vec3_unit(self.direction);
  float alpha = 0.5f * (unit_direction.y + 1.0f);

  Color3 white = { 1.0f, 1.0f, 1.0f };
  Color3 sky_blue = { 0.5f, 0.7f, 1.0f };

  return vec3_lerp(white, sky_blue, alpha);
}
