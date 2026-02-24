typedef struct {
  Texture *tex;
} DiffuseLight;

static Color3 diffuse_light_emitted(const DiffuseLight *d, float u, float v, Point3 p) {
  return texture_color_value(d->tex, u, v, p);
}
