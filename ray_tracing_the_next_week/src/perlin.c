#define POINT_COUNT 256

typedef struct {
  float randfloat[POINT_COUNT];
  int perm_x[POINT_COUNT];
  int perm_y[POINT_COUNT];
  int perm_z[POINT_COUNT];
} Perlin;

static Perlin perlin_generate(void) {
  Perlin perlin = {0};

  for (int i = 0; i < POINT_COUNT; i++) {
    perlin.randfloat[i] = random_float();
    perlin.perm_x[i] = i;
    perlin.perm_y[i] = i;
    perlin.perm_z[i] = i;
  }

  random_permute(perlin.perm_x, POINT_COUNT);
  random_permute(perlin.perm_y, POINT_COUNT);
  random_permute(perlin.perm_z, POINT_COUNT);

  return perlin;
}

static float perlin_trilinear_interp(float c[2][2][2], float u, float v, float w) {
  float accum = 0.0f;

  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++)
      for (int k = 0; k < 2; k++)
        accum +=
          (i * u + (1 - i) * (1 - u)) *
          (j * v + (1 - j) * (1 - v)) *
          (k * w + (1 - k) * (1 - w)) *
          c[i][j][k];

  return accum;
}

static float perlin_noise(Perlin *p, Point3 point) {
  float u = point.coord.x - floorf(point.coord.x);
  float v = point.coord.y - floorf(point.coord.y);
  float w = point.coord.z - floorf(point.coord.z);

  u = u * u * (3 - 2 * u);
  v = v * v * (3 - 2 * v);
  w = w * w * (3 - 2 * w);

  int i = (int)(floorf(point.coord.x));
  int j = (int)(floorf(point.coord.y));
  int k = (int)(floorf(point.coord.z));

  float c[2][2][2];

  for (int di = 0; di < 2; di++)
    for (int dj = 0; dj < 2; dj++)
      for (int dk = 0; dk < 2; dk++)
        c[di][dj][dk] = p->randfloat[
          p->perm_x[(i+di) & 255] ^
          p->perm_y[(j+dj) & 255] ^
          p->perm_z[(k+dk) & 255]
        ];

  return perlin_trilinear_interp(c, u, v, w);
}
