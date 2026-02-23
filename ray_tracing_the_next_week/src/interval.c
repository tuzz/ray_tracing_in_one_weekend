typedef struct {
  float min, max;
} Interval;

static const Interval INTERVAL_EMPTY = {FLT_MAX, -FLT_MAX};
static const Interval INTERVAL_UNIVERSE = {-FLT_MAX, FLT_MAX};

static Interval interval_from(float a, float b) {
  return a <= b ? (Interval){a, b} : (Interval){b, a};
}

static Interval interval_union(Interval a, Interval b) {
  return (Interval){
    a.min <= b.min ? a.min : b.min,
    a.max >= b.max ? a.max : b.max,
  };
}

static float interval_size(Interval i) {
  return i.max - i.min;
}

static bool interval_contains(Interval i, float x) {
  return i.min <= x && x <= i.max;
}

static bool interval_surrounds(Interval i, float x) {
  return i.min < x && x < i.max;
}

static float interval_clamp(Interval i, float x) {
  if (x < i.min) return i.min;
  if (x > i.max) return i.max;
  return x;
}
