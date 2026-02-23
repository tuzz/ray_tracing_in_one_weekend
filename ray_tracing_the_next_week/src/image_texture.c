typedef struct {
  Image *image;
} ImageTexture;

static Color3 image_texture_value(const ImageTexture *t, float u, float v, Point3 p) {
  u = interval_clamp((Interval){0.0f, 1.0f}, u);
  v = 1.0f - interval_clamp((Interval){0.0f, 1.0f}, v);

  int i = (int)(u * t->image->image_width);
  int j = (int)(v * t->image->image_height);
  const unsigned char *pixel = image_pixel_data(t->image, i, j);

  float color_scale = 1.0f / 255.0f;
  return (Color3){{color_scale * pixel[0], color_scale * pixel[1], color_scale * pixel[2]}};
}
