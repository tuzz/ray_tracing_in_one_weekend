#define MAX_HITTABLES 100

typedef struct {
  Hittable items[MAX_HITTABLES];
  size_t length;
} HittableList;

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


static bool hittable_list_hit(const Hittable *base, const Ray3 *ray, float ray_tmin, float ray_tmax, Hit *hit) {
  const HittableList *h = (const HittableList *)base;

  Hit tmp_hit;
  bool hit_anything = false;
  float closest_so_far = ray_tmax;

  for (const Hittable *object = h->items; object < &h->items[h->length]; object++) {
    if (object->hit(object, ray, ray_tmin, closest_so_far, &tmp_hit)) {
      hit_anything = true;
      closest_so_far = tmp_hit.t;
      *hit = tmp_hit;
    }
  }

  return hit_anything;
}
