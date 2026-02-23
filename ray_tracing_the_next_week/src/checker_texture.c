struct CheckerTexture {
  float inv_scale;
  Texture *even;
  Texture *odd;
};

static Color3 checker_texture_value(const CheckerTexture *c, float u, float v, Point3 p) {
  int x = (int)(floorf(c->inv_scale * p.coord.x));
  int y = (int)(floorf(c->inv_scale * p.coord.y));
  int z = (int)(floorf(c->inv_scale * p.coord.z));

  bool is_even = (x + y + z) % 2 == 0;
  return is_even ? texture_color_value(c->even, u, v, p) : texture_color_value(c->odd, u, v, p);
}
