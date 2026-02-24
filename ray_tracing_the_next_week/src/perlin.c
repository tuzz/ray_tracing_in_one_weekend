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

static float perlin_noise(Perlin *p, Point3 point) {
  int i = positive_mod((int)(4 * point.coord.x), POINT_COUNT - 1);
  int j = positive_mod((int)(4 * point.coord.y), POINT_COUNT - 1);
  int k = positive_mod((int)(4 * point.coord.z), POINT_COUNT - 1);

  return p->randfloat[p->perm_x[i] ^ p->perm_y[j] ^ p->perm_z[k]];
}
