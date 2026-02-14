typedef struct {
  Hittable base;
  Point3 center;
  float radius;
} Sphere;

static bool sphere_hit(const Hittable *self, const Ray3 *ray, float ray_tmin, float ray_tmax, HitRecord *record) {
  const Sphere *sphere = (const Sphere *)self;

  Vec3 oc = vec3_subtract(sphere->center, ray->origin);
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

  Point3 sphere_point = ray3_at(*ray, root);
  Vec3 sphere_normal = vec3_subtract(sphere_point, sphere->center);
  Vec3 sphere_unit_normal = vec3_scale(sphere_normal, 1.0f / sphere->radius);

  record->t = root;
  record->p = sphere_point;
  record->normal = sphere_unit_normal;

  return true;
}
