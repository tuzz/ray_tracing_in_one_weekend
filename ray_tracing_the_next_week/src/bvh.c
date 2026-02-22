typedef struct {
  Hittable *left;
  Hittable *right;
  AABB bbox;
} BVH;

static bool bvh_hit(const BVH *bvh, const Ray3 *ray, Interval ray_t, Hit *hit) {
  if (!aabb_hit(&bvh->bbox, ray, ray_t)) return false;

  bool hit_left = hittable_hit(bvh->left, ray, ray_t, hit);
  if (hit_left) ray_t.max = hit->t;

  bool hit_right = hittable_hit(bvh->right, ray, ray_t, hit);
  return hit_left || hit_right;
}
