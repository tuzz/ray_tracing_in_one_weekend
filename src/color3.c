typedef Vec3 Color3;

static const Color3 WHITE = {1.0f, 1.0f, 1.0f};
static const Color3 SKY_BLUE = {0.5f, 0.7f, 1.0f};

static void color3_write_line(Color3 c, FILE *f) {
  int red = (int)(255.999f * c.x);
  int green = (int)(255.999f * c.y);
  int blue = (int)(255.999f * c.z);

  fprintf(f, "%d %d %d\n", red, green, blue);
}
