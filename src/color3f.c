typedef Vector3f Color3f;

static void color3f_write_line(Vector3f self, FILE *stream) {
  int red = (int)(255.999f * self.x);
  int green = (int)(255.999f * self.y);
  int blue = (int)(255.999f * self.z);

  fprintf(stream, "%d %d %d\n", red, green, blue);
}
