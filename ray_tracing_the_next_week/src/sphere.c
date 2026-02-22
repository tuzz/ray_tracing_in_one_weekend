typedef struct {
  Point3 center;
  float radius;
  Material *material;
} Sphere;

static bool sphere_hit(const Sphere *s, const Ray3 *ray, Interval ray_t, Hit *hit) {
  Vec3 oc = vec3_sub(s->center, ray->origin);
  float a = vec3_length_squared(ray->direction);
  float h = vec3_dot(ray->direction, oc);
  float c = vec3_length_squared(oc) - s->radius * s->radius;

  float discriminant = h * h - a * c;
  if (discriminant < 0) return false;

  float sqrt = sqrtf(discriminant);
  float root = (h - sqrt) / a;

  if (!interval_surrounds(ray_t, root)) {
    root = (h + sqrt) / a;
    if (!interval_surrounds(ray_t, root)) return false;
  }

  Point3 intersection = ray3_at(*ray, root);
  Vec3 normal = vec3_sub(intersection, s->center);
  Vec3 unit_normal = vec3_scale(normal, 1.0f / s->radius);

  hit->t = root;
  hit->p = intersection;
  hit_set_face_normal(hit, ray, unit_normal);
  hit->material = s->material;

  return true;
}
