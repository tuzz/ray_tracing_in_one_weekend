typedef Vec3 Color3;

static const Color3 BLACK = {0.0f, 0.0f, 0.0f};
static const Color3 WHITE = {1.0f, 1.0f, 1.0f};
static const Color3 SKY_BLUE = {0.5f, 0.7f, 1.0f};

static void color3_write_line(Color3 c, FILE *f) {
  float r = linear_to_gamma(c.x);
  float g = linear_to_gamma(c.y);
  float b = linear_to_gamma(c.z);

  static const Interval intensity = {0.0f, 0.999f};
  int red = (int)(256.0f * interval_clamp(intensity, r));
  int green = (int)(256.0f * interval_clamp(intensity, g));
  int blue = (int)(256.0f * interval_clamp(intensity, b));

  fprintf(f, "%d %d %d\n", red, green, blue);
}
