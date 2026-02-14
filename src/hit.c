typedef struct {
  Point3 p;
  Vec3 normal;
  float t;
  bool front_face;
} Hit;

static void hit_set_face_normal(Hit *hit, const Ray3 *ray, const Vec3 outward_normal) {
  hit->front_face = vec3_dot(ray->direction, outward_normal) < 0.0f;
  hit->normal = hit->front_face ? outward_normal : vec3_neg(outward_normal);
}
