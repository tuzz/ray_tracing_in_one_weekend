typedef struct {
  Ray3 center;
  float radius;
  Material *material;
  AABB bbox;
} Sphere;

static Sphere sphere_new(Ray3 center, float radius, Material *material) {
  Vec3 rvec = {{radius, radius, radius}};
  Point3 center1 = ray3_at(center, 0.0f);
  Point3 center2 = ray3_at(center, 1.0f);
  AABB box1 = aabb_from_points(vec3_sub(center1, rvec), vec3_add(center1, rvec));
  AABB box2 = aabb_from_points(vec3_sub(center2, rvec), vec3_add(center2, rvec));

  return (Sphere){.center = center, .radius = radius, .material = material, .bbox = aabb_union(&box1, &box2)};
}

static bool sphere_hit(const Sphere *s, const Ray3 *ray, Interval ray_t, Hit *hit) {
  Point3 current_center = ray3_at(s->center, ray->time);
  Vec3 oc = vec3_sub(current_center, ray->origin);
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
  Vec3 normal = vec3_sub(intersection, current_center);
  Vec3 unit_normal = vec3_scale(normal, 1.0f / s->radius);

  hit->t = root;
  hit->p = intersection;
  hit_set_face_normal(hit, ray, unit_normal);
  hit->material = s->material;

  return true;
}
