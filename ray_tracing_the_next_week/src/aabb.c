typedef union {
  Interval intervals[3];
  struct { Interval x, y, z; } interval;
} AABB;

static const AABB AABB_EMPTY = {{INTERVAL_EMPTY, INTERVAL_EMPTY, INTERVAL_EMPTY}};
static const AABB AABB_UNIVERSE = {{INTERVAL_UNIVERSE, INTERVAL_UNIVERSE, INTERVAL_UNIVERSE}};

static AABB aabb_from_points(Point3 a, Point3 b) {
  Interval x = interval_from(a.coord.x, b.coord.x);
  Interval y = interval_from(a.coord.y, b.coord.y);
  Interval z = interval_from(a.coord.z, b.coord.z);

  float delta = 0.0001f;
  if (interval_size(x) < delta) x = interval_expand(x, delta);
  if (interval_size(y) < delta) x = interval_expand(y, delta);
  if (interval_size(z) < delta) x = interval_expand(z, delta);

  return (AABB){{x, y, z}};
}

static AABB aabb_union(const AABB *a, const AABB *b) {
  return (AABB){{
    interval_union(a->interval.x, b->interval.x),
    interval_union(a->interval.y, b->interval.y),
    interval_union(a->interval.z, b->interval.z),
  }};
}

static bool aabb_hit(const AABB *aabb, const Ray3 *ray, Interval ray_t) {
  for (int axis = 0; axis < 3; axis++) {
    Interval interval = aabb->intervals[axis];
    float adinv = 1.0f / ray->direction.coords[axis];

    float t0 = (interval.min - ray->origin.coords[axis]) * adinv;
    float t1 = (interval.max - ray->origin.coords[axis]) * adinv;

    if (t0 < t1) {
      if (t0 > ray_t.min) ray_t.min = t0;
      if (t1 < ray_t.max) ray_t.max = t1;
    } else {
      if (t1 > ray_t.min) ray_t.min = t1;
      if (t0 < ray_t.max) ray_t.max = t0;
    }

    if (ray_t.max <= ray_t.min) return false;
  }

  return true;
}

static int aabb_longest_axis(const AABB *aabb) {
  float x_size = interval_size(aabb->interval.x);
  float y_size = interval_size(aabb->interval.y);
  float z_size = interval_size(aabb->interval.z);

  if (x_size > y_size) {
    return x_size > z_size ? 0 : 2;
  } else {
    return y_size > z_size ? 1 : 2;
  }
}
