typedef struct {
  Point3 origin;
  Vec3 direction;
} Ray3;

static Point3 ray3_at(Ray3 self, float t) {
  return vec3_add(self.origin, vec3_scale(self.direction, t));
}

static Color3 ray3_color(Ray3 self) {
  return (Color3){ 0.0f, 0.0f, 0.0f };
}
