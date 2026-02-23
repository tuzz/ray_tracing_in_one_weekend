typedef struct {
  int bytes_per_pixel;
  float *fdata;
  unsigned char *bdata;
  int image_width;
  int image_height;
  int bytes_per_scanline;
} Image;

static Image image_load(char *path) {
  Image image = {0};

  int n = image.bytes_per_pixel;
  image.fdata = stbi_loadf(path, &image.image_width, &image.image_height, &n, image.bytes_per_pixel);
  if (!image.fdata) {
    fprintf(stderr, "Failed to load image\n");
    exit(EXIT_FAILURE);
  }

  image.bytes_per_pixel = n;
  image.bytes_per_scanline = image.image_width * image.bytes_per_pixel;

  int total_bytes = image.image_width * image.image_height * image.bytes_per_pixel;
  image.bdata = malloc(total_bytes);

  for (int i = 0; i < total_bytes; i++) {
    float value = image.fdata[i];
    unsigned char byte;

    if (value <= 0.0f) {
      byte = 0;
    } else if (value >= 1.0f) {
      byte = 255;
    } else {
      byte = (unsigned char)(256.0f * value);
    }

    image.bdata[i] = byte;
  }

  return image;
}

static void image_free(const Image *image) {
  free(image->bdata);
  STBI_FREE(image->fdata);
}

static int image_clamp(int x, int low, int high) {
  if (x < low) return low;
  if (x < high) return x;
  return high - 1;
}

static const unsigned char *image_pixel_data(const Image *image, int x, int y) {
  static unsigned char pixel[] = {0, 0, 0};

  x = image_clamp(x, 0, image->image_width);
  y = image_clamp(y, 0, image->image_height);

  return image->bdata + y * image->bytes_per_scanline + x * image->bytes_per_pixel;
}
