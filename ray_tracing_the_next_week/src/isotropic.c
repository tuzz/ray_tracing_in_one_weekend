typedef struct {
  Texture *tex;
} Isotropic;

static bool isotropic_scatter(const Isotropic *i, const Ray3 *ray, const Hit *hit, Color3 *attentuation, Ray3 *scattered) {
  *scattered = (Ray3){.origin = hit->p, .direction = vec3_random_unit(), ray->time};

  // Note: u, v are not set by ConstantMedium so we must use a texture that doesn't depend on them.
  *attentuation = texture_color_value(i->tex, hit->u, hit->v, hit->p);

  return true;
}
