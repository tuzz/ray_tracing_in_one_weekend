typedef Vec3 Color3;

static void color3_write_line(Color3 c, FILE *f) {
  int red = (int)(255.999f * c.x);
  int green = (int)(255.999f * c.y);
  int blue = (int)(255.999f * c.z);

  fprintf(f, "%d %d %d\n", red, green, blue);
}
