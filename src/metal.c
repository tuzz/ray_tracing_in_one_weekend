typedef struct {
  Color3 albedo;
} Metal;

static bool metal_scatter(const Metal *m, const Ray3 *ray, const Hit *hit, Color3 *attentuation, Ray3 *scattered) {
  Vec3 reflected = vec3_reflect(ray->direction, hit->normal);

  *scattered = (Ray3){.origin = hit->p, .direction = reflected};
  *attentuation = m->albedo;
  return true;
}
