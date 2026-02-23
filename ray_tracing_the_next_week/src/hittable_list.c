#define MAX_HITTABLES 1000

struct HittableList {
  Hittable items[MAX_HITTABLES];
  size_t length;
  AABB bbox;
};

static HittableList hittable_list_new(void) {
  return (HittableList){.bbox = aabb_empty()};
}

static void hittable_list_clear(HittableList *h) {
  h->length = 0;
}

static void hittable_list_add(HittableList *h, Hittable hittable) {
  if (h->length == MAX_HITTABLES) {
    fprintf(stderr, "HittableList is full\n");
    exit(EXIT_FAILURE);
  }

  AABB bbox = hittable_bounding_box(&hittable);

  h->items[h->length++] = hittable;
  h->bbox = aabb_union(&h->bbox, &bbox);
}

static bool hittable_list_hit(const HittableList *h, const Ray3 *ray, Interval ray_t, Hit *hit) {
  Hit tmp_hit;
  bool hit_anything = false;
  float closest_so_far = ray_t.max;

  for (size_t i = 0; i < h->length; i++) {
    if (hittable_hit(&h->items[i], ray, (Interval){ray_t.min, closest_so_far}, &tmp_hit)) {
      hit_anything = true;
      closest_so_far = tmp_hit.t;
      *hit = tmp_hit;
    }
  }

  return hit_anything;
}

static AABB hittable_list_bounding_box(const HittableList *h) {
  return h->bbox;
}
