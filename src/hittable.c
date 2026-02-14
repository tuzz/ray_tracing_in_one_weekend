typedef struct Hittable {
  bool (*hit)(const struct Hittable *base, const Ray3 *ray, float ray_tmin, float ray_tmax, Hit *hit);
} Hittable;
