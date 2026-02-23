// Forward declare HittableList to break recursive definition.
typedef struct HittableList HittableList;
static bool hittable_list_hit(const HittableList *h, const Ray3 *ray, Interval ray_t, Hit *hit);
static AABB hittable_list_bounding_box(const HittableList *h);

typedef struct BVHNode BVHNode;
static bool bvh_node_hit(const BVHNode *n, const Ray3 *ray, Interval ray_t, Hit *hit);
static AABB bvh_node_bounding_box(const BVHNode *n);

typedef enum {
  HITTABLE_SPHERE,
  HITTABLE_LIST,
  HITTABLE_BVH_NODE,
} HittableType;

typedef struct Hittable {
  HittableType type;
  union {
    Sphere sphere;
    HittableList *list;
    BVHNode *node;
  } u;
} Hittable;

static bool hittable_hit(const Hittable *h, const Ray3 *ray, Interval ray_t, Hit *hit) {
  switch (h->type) {
    case HITTABLE_SPHERE:
      return sphere_hit(&h->u.sphere, ray, ray_t, hit);
    case HITTABLE_LIST:
      return hittable_list_hit(h->u.list, ray, ray_t, hit);
    case HITTABLE_BVH_NODE:
      return bvh_node_hit(h->u.node, ray, ray_t, hit);
    default:
      assert(false && "Unknown HittableType");
  }
}

static AABB hittable_bounding_box(const Hittable *h) {
  switch (h->type) {
    case HITTABLE_SPHERE:
      return h->u.sphere.bbox;
    case HITTABLE_LIST:
      return hittable_list_bounding_box(h->u.list);
    case HITTABLE_BVH_NODE:
      return bvh_node_bounding_box(h->u.node);
    default:
      assert(false && "Unknown HittableType");
  }
}
