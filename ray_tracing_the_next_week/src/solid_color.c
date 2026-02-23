typedef struct {
  Color3 albedo;
} SolidColor;

static Color3 solid_color_value(const SolidColor *s, float u, float v, Point3 p) {
  return s->albedo;
}
