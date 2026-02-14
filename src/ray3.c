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
