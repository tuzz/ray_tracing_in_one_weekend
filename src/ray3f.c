typedef struct {
  Point3f origin;
  Vector3f direction;
} Ray3f;

static Point3f ray3f_at(Ray3f self, float t) {
  return vector3f_add(self.origin, vector3f_scale(self.direction, t));
}

static Color3f ray3f_color(Ray3f self) {
  return (Color3f){ 0.0f, 0.0f, 0.0f };
}
