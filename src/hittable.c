// Forward declare HittableList to break recursive definition.
typedef struct HittableList HittableList;
static bool hittable_list_hit(const HittableList *h, const Ray3 *ray, Interval ray_t, Hit *hit);

typedef enum {
  HITTABLE_SPHERE,
  HITTABLE_LIST,
} HittableType;

typedef struct Hittable {
  HittableType type;
  union {
    Sphere sphere;
    HittableList *list;
  } u;
} Hittable;

static bool hittable_hit(const Hittable *h, const Ray3 *ray, Interval ray_t, Hit *hit) {
  switch (h->type) {
    case HITTABLE_SPHERE:
      return sphere_hit(&h->u.sphere, ray, ray_t, hit);
    case HITTABLE_LIST:
      return hittable_list_hit(h->u.list, ray, ray_t, hit);
    default:
      assert(false && "Unknown HittableType");
  }
}
