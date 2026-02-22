typedef struct {
  Color3 albedo;
  float fuzz;
} Metal;

static bool metal_scatter(const Metal *m, const Ray3 *ray, const Hit *hit, Color3 *attentuation, Ray3 *scattered) {
  Vec3 reflected = vec3_reflect(ray->direction, hit->normal);
  reflected = vec3_add(vec3_unit(reflected), vec3_scale(vec3_random_unit(), m->fuzz));

  *scattered = (Ray3){.origin = hit->p, .direction = reflected};
  *attentuation = m->albedo;

  return vec3_dot(scattered->direction, hit->normal) > 0.0f;
}
