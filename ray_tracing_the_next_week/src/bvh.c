#define MAX_BVH_NODES 2000

struct BVHNode {
  Hittable *left;
  Hittable *right;
  AABB bbox;
};

typedef struct {
  Hittable hittables[MAX_BVH_NODES];
  BVHNode nodes[MAX_BVH_NODES];
  size_t length;
} BVH;

static int bvh_compare(const Hittable *a, const Hittable *b, int axis) {
  Interval i1 = hittable_bounding_box(a).intervals[axis];
  Interval i2 = hittable_bounding_box(b).intervals[axis];
  return i1.min < i2.min ? -1 : i1.min > i2.min ? 1 : 0;
}

static int bvh_compare_x(const void *a, const void *b) { return bvh_compare(a, b, 0); }
static int bvh_compare_y(const void *a, const void *b) { return bvh_compare(a, b, 1); }
static int bvh_compare_z(const void *a, const void *b) { return bvh_compare(a, b, 2); }

static Hittable *bvh_node(BVH *bvh, Hittable *hittables, size_t start, size_t end) {
  if (bvh->length == MAX_BVH_NODES) {
    fprintf(stderr, "BVH is full\n");
    exit(EXIT_FAILURE);
  }

  Hittable *hittable = &bvh->hittables[bvh->length];
  BVHNode *node = &bvh->nodes[bvh->length++];
  hittable->type = HITTABLE_BVH_NODE;
  hittable->u.node = node;

  size_t object_span = end - start;

  if (object_span == 1) {
    node->left = node->right = &hittables[start];
  } else if (object_span == 2) {
    node->left = &hittables[start];
    node->right = &hittables[start + 1];
  } else {
    AABB bbox = AABB_EMPTY;

    for (size_t i = start; i < end; i++) {
      AABB hittable_box = hittable_bounding_box(&hittables[i]);
      bbox = aabb_union(&bbox, &hittable_box);
    }

    int axis = aabb_longest_axis(&bbox);
    qsort(hittables + start, object_span, sizeof(Hittable), axis == 0 ? bvh_compare_x : axis == 1 ? bvh_compare_y : bvh_compare_z);

    size_t mid = start + object_span / 2;
    node->left = bvh_node(bvh, hittables, start, mid);
    node->right = bvh_node(bvh, hittables, mid, end);
  }

  AABB bbox1 = hittable_bounding_box(node->left);
  AABB bbox2 = hittable_bounding_box(node->right);
  node->bbox = aabb_union(&bbox1, &bbox2);

  return hittable;
}

static bool bvh_node_hit(const BVHNode *node, const Ray3 *ray, Interval ray_t, Hit *hit) {
  if (!aabb_hit(&node->bbox, ray, ray_t)) return false;

  bool hit_left = hittable_hit(node->left, ray, ray_t, hit);
  if (hit_left) ray_t.max = hit->t;

  bool hit_right = hittable_hit(node->right, ray, ray_t, hit);
  return hit_left || hit_right;
}

static AABB bvh_node_bounding_box(const BVHNode *n) {
  return n->bbox;
}
