typedef struct {
  Point3 p;
  Vec3 normal;
  float t;
} HitRecord;

typedef struct Hittable {
  bool (*hit)(const struct Hittable *self, const Ray3 *ray, float t_min, float t_max, HitRecord *rec);
} Hittable;
