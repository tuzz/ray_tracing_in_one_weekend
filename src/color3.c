typedef Vec3 Color3;

static void color3_write_line(Vec3 self, FILE *stream) {
  int red = (int)(255.999f * self.x);
  int green = (int)(255.999f * self.y);
  int blue = (int)(255.999f * self.z);

  fprintf(stream, "%d %d %d\n", red, green, blue);
}
