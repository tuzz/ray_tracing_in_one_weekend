typedef struct {
  Color3 albedo;
} Lambertian;

static bool lambertian_scatter(const Lambertian *l, const Ray3 *ray, const Hit *hit, Color3 *attentuation, Ray3 *scattered) {
  Vec3 scatter_direction = vec3_add(hit->normal, vec3_random_unit());
  if (vec3_near_zero(scatter_direction)) scatter_direction = hit->normal;

  *scattered = (Ray3){.origin = hit->p, .direction = scatter_direction};
  *attentuation = l->albedo;
  return true;
}
