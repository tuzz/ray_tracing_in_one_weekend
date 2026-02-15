typedef struct {
  float refaction_index;
} Dielectric;

static bool dielectric_scatter(const Dielectric *d, const Ray3 *ray, const Hit *hit, Color3 *attentuation, Ray3 *scattered) {
  *attentuation = WHITE;
  float ri = hit->front_face ? (1.0f / d->refaction_index) : d->refaction_index;

  Vec3 unit_direction = vec3_unit(ray->direction);
  Vec3 refracted = vec3_refract(unit_direction, hit->normal, ri);

  *scattered = (Ray3){.origin = hit->p, .direction = refracted};
  return true;
}
