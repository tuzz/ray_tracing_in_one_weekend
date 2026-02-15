#define MAX_HITTABLES 1000

struct HittableList {
  Hittable items[MAX_HITTABLES];
  size_t length;
};

static void hittable_list_clear(HittableList *h) {
  h->length = 0;
}

static void hittable_list_add(HittableList *h, Hittable hittable) {
  if (h->length == MAX_HITTABLES) {
    fprintf(stderr, "HittableList is full\n");
    exit(EXIT_FAILURE);
  }

  h->items[h->length++] = hittable;
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
