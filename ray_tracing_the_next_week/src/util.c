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

static float linear_to_gamma(float linear_component) {
  return linear_component > 0 ? sqrtf(linear_component) : 0.0f;
}
