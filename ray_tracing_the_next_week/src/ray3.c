typedef struct {
  Point3 origin;
  Vec3 direction;
  float time;
} Ray3;

static Point3 ray3_at(const Ray3 *r, float t) {
  return vec3_add(r->origin, vec3_scale(r->direction, t));
}
