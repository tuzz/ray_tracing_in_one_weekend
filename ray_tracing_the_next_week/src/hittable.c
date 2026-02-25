// Forward declare HittableList to break recursive definition.
typedef struct HittableList HittableList;
static bool hittable_list_hit(const HittableList *h, const Ray3 *ray, Interval ray_t, Hit *hit);
static AABB hittable_list_bounding_box(const HittableList *h);

typedef struct BVHNode BVHNode;
static bool bvh_node_hit(const BVHNode *n, const Ray3 *ray, Interval ray_t, Hit *hit);
static AABB bvh_node_bounding_box(const BVHNode *n);

typedef struct Translate Translate;
static bool translate_hit(const Translate *t, const Ray3 *ray, Interval ray_t, Hit *hit);
static AABB translate_bounding_box(const Translate *t);

typedef struct RotateY RotateY;
static bool rotate_y_hit(const RotateY *r, const Ray3 *ray, Interval ray_t, Hit *hit);
static AABB rotate_y_bounding_box(const RotateY *t);

typedef enum {
  HITTABLE_SPHERE,
  HITTABLE_QUAD,
  HITTABLE_LIST,
  HITTABLE_BVH_NODE,
  HITTABLE_TRANSLATE,
  HITTABLE_ROTATE_Y,
} HittableType;

typedef struct Hittable {
  HittableType type;
  union {
    Sphere sphere;
    Quad quad;
    HittableList *list;
    BVHNode *node;
    Translate *translate;
    RotateY *rotate_y;
  } u;
} Hittable;

static bool hittable_hit(const Hittable *h, const Ray3 *ray, Interval ray_t, Hit *hit) {
  switch (h->type) {
    case HITTABLE_SPHERE:
      return sphere_hit(&h->u.sphere, ray, ray_t, hit);
    case HITTABLE_QUAD:
      return quad_hit(&h->u.quad, ray, ray_t, hit);
    case HITTABLE_LIST:
      return hittable_list_hit(h->u.list, ray, ray_t, hit);
    case HITTABLE_BVH_NODE:
      return bvh_node_hit(h->u.node, ray, ray_t, hit);
    case HITTABLE_TRANSLATE:
      return translate_hit(h->u.translate, ray, ray_t, hit);
    case HITTABLE_ROTATE_Y:
      return rotate_y_hit(h->u.rotate_y, ray, ray_t, hit);
    default:
      assert(false && "Unknown HittableType");
  }
}

static AABB hittable_bounding_box(const Hittable *h) {
  switch (h->type) {
    case HITTABLE_SPHERE:
      return h->u.sphere.bbox;
    case HITTABLE_QUAD:
      return h->u.quad.bbox;
    case HITTABLE_LIST:
      return hittable_list_bounding_box(h->u.list);
    case HITTABLE_BVH_NODE:
      return bvh_node_bounding_box(h->u.node);
    case HITTABLE_TRANSLATE:
      return translate_bounding_box(h->u.translate);
    case HITTABLE_ROTATE_Y:
      return rotate_y_bounding_box(h->u.rotate_y);
    default:
      assert(false && "Unknown HittableType");
  }
}
