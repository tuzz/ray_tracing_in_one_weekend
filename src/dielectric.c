typedef struct {
  float refaction_index;
} Dielectric;

static float dielectric_reflectance(float cosine, float refraction_index) {
  float r0 = (1.0f - refraction_index) / (1.0f + refraction_index);
  r0 = r0 * r0;
  return r0 + (1.0f - r0) * powf((1.0f - cosine), 5.0f);
}

static bool dielectric_scatter(const Dielectric *d, const Ray3 *ray, const Hit *hit, Color3 *attentuation, Ray3 *scattered) {
  *attentuation = WHITE;
  float ri = hit->front_face ? (1.0f / d->refaction_index) : d->refaction_index;

  Vec3 unit_direction = vec3_unit(ray->direction);
  float cos_theta = fminf(vec3_dot(vec3_neg(unit_direction), hit->normal), 1.0f);
  float sin_theta = sqrtf(1.0f - cos_theta * cos_theta);

  bool cannot_refract = ri * sin_theta > 1.0f;
  Vec3 direction;

  if (cannot_refract || dielectric_reflectance(cos_theta, ri) > random_float()) {
    direction = vec3_reflect(unit_direction, hit->normal);
  } else {
    direction = vec3_refract(unit_direction, hit->normal, ri);
  }

  *scattered = (Ray3){.origin = hit->p, .direction = direction};
  return true;
}
