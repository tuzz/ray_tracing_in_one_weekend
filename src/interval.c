typedef struct {
  float min, max;
} Interval;

static const Interval INTERVAL_EMPTY = {INFINITY, -INFINITY};
static const Interval INTERVAL_UNIVERSE = {-INFINITY, INFINITY};

static float interval_size(Interval i) {
  return i.max - i.min;
}

static bool interval_contains(Interval i, float x) {
  return i.min <= x && x <= i.max;
}

static bool interval_surrounds(Interval i, float x) {
  return i.min < x && x < i.max;
}
