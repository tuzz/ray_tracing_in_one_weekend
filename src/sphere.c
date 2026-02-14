typedef struct {
  Hittable base;
  Point3 center;
  float radius;
} Sphere;

static bool sphere_hit(const Hittable *base, const Ray3 *ray, float ray_tmin, float ray_tmax, Hit *hit) {
  const Sphere *sphere = (const Sphere *)base;

  Vec3 oc = vec3_sub(sphere->center, ray->origin);
  float a = vec3_length_squared(ray->direction);
  float h = vec3_dot(ray->direction, oc);
  float c = vec3_length_squared(oc) - sphere->radius * sphere->radius;

  float discriminant = h * h - a * c;
  if (discriminant < 0) return false;

  float sqrt = sqrtf(discriminant);
  float root = (h - sqrt) / a;

  if (root <= ray_tmin || ray_tmax <= root) {
    root = (h + sqrt) / a;
    if (root <= ray_tmin || ray_tmax <= root) return false;
  }

  Point3 intersection = ray3_at(*ray, root);
  Vec3 normal = vec3_sub(intersection, sphere->center);
  Vec3 unit_normal = vec3_scale(normal, 1.0f / sphere->radius);

  hit->t = root;
  hit->p = intersection;
  hit_set_face_normal(hit, ray, unit_normal);

  return true;
}
