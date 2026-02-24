#define PI 3.1415926535897932385f

static float degrees_to_radians(float degrees) {
  return degrees * PI / 180.0f;
}

static float random_float(void) {
  return rand() / (float)RAND_MAX;
}

static float random_between(float min, float max) {
  return min + (max - min) * random_float();
}

static int random_int(int min, int max) {
  return (int)(random_between(min, max + 1));
}

static void random_permute(int *array, int n) {
  for (int i = n - 1; i > 0; i--) {
    int target = random_int(0, i);
    int tmp = array[i];
    array[i] = array[target];
    array[target] = tmp;
  }
}

static float linear_to_gamma(float linear_component) {
  return linear_component > 0 ? sqrtf(linear_component) : 0.0f;
}

static int positive_mod(int i, int n) {
  return (i % n + n) % n;
}
