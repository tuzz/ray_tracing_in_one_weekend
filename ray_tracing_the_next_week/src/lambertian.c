typedef struct {
  Texture *tex;
} Lambertian;

static bool lambertian_scatter(const Lambertian *l, const Ray3 *ray, const Hit *hit, Color3 *attentuation, Ray3 *scattered) {
  Vec3 scatter_direction = vec3_add(hit->normal, vec3_random_unit());
  if (vec3_near_zero(scatter_direction)) scatter_direction = hit->normal;

  *scattered = (Ray3){.origin = hit->p, .direction = scatter_direction, .time = ray->time};
  *attentuation = texture_color_value(l->tex, hit->u, hit->v, hit->p);
  return true;
}
