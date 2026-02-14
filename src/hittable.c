typedef struct Hittable {
  bool (*hit)(const struct Hittable *base, const Ray3 *ray, float t_min, float t_max, Hit *hit);
} Hittable;
