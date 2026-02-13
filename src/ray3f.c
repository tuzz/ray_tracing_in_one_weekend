typedef struct {
  Point3f origin;
  Vector3f direction;
} Ray3f;

static Point3f ray3f_at(const Ray3f *self, float t) {
  Vector3f scaled_direction = vector3f_scale(&self->direction, t);
  return vector3f_add(&self->origin, &scaled_direction);
}

static Color3f ray3f_color(const Ray3f *self) {
  return (Color3f){ 0.0f, 0.0f, 0.0f };
}
