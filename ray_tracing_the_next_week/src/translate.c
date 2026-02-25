struct Translate {
  Hittable *hittable;
  Vec3 offset;
  AABB bbox;
};

static Translate translate_new(Hittable *hittable, Vec3 offset) {
  AABB bbox = hittable_bounding_box(hittable);
  bbox = aabb_add_vec3(&bbox, offset);

  return (Translate){hittable, offset, bbox};
}

static bool translate_hit(const Translate *t, const Ray3 *ray, Interval ray_t, Hit *hit) {
  Ray3 offset_r = (Ray3){.origin = vec3_sub(ray->origin, t->offset), .direction = ray->direction, .time = ray->time};

  if (!hittable_hit(t->hittable, &offset_r, ray_t, hit)) return false;

  hit->p = vec3_add(hit->p, t->offset);

  return true;
}

static AABB translate_bounding_box(const Translate *t) {
  return t->bbox;
}
