typedef struct {
  Point3 origin;
  Vec3 direction;
} Ray3;

static Point3 ray3_at(Ray3 r, float t) {
  return vec3_add(r.origin, vec3_scale(r.direction, t));
}
