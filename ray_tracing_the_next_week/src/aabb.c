typedef union {
  Interval intervals[3];
  struct { Interval x, y, z; } interval;
} AABB;

static AABB aabb_empty(void) {
  return (AABB){{INTERVAL_EMPTY, INTERVAL_EMPTY, INTERVAL_EMPTY}};
}

static AABB aabb_from_points(Point3 a, Point3 b) {
  return (AABB){{
    interval_from(a.coord.x, b.coord.x),
    interval_from(a.coord.y, b.coord.y),
    interval_from(a.coord.z, b.coord.z),
  }};
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
