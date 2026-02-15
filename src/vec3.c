typedef struct {
  float x, y, z;
} Vec3;

static Vec3 vec3_neg(Vec3 v) {
  return (Vec3){-v.x, -v.y, -v.z};
}

static Vec3 vec3_add(Vec3 a, Vec3 b) {
  return (Vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

static Vec3 vec3_sub(Vec3 a, Vec3 b) {
  return (Vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

static Vec3 vec3_mul(Vec3 a, Vec3 b) {
  return (Vec3){a.x * b.x, a.y * b.y, a.z * b.z};
}

static Vec3 vec3_scale(Vec3 v, float s) {
  return (Vec3){v.x * s, v.y * s, v.z * s};
}

static float vec3_dot(Vec3 a, Vec3 b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

static Vec3 vec3_cross(Vec3 a, Vec3 b) {
  return (Vec3){
    a.y * b.z - a.z * b.y,
    a.z * b.x - a.x * b.z,
    a.x * b.y - a.y * b.x,
  };
}

static float vec3_length_squared(Vec3 v) {
  return v.x * v.x + v.y * v.y + v.z * v.z;
}

static float vec3_length(Vec3 v) {
  return sqrtf(vec3_length_squared(v));
}

static bool vec3_near_zero(Vec3 v) {
  return fabsf(v.x) < 1e-8f && fabsf(v.y) < 1e-8f && fabsf(v.z) < 1e-8f;
}

static Vec3 vec3_random(void) {
  return (Vec3){random_float(), random_float(), random_float()};
}

static Vec3 vec3_random_between(float min, float max) {
  return (Vec3){random_between(min, max), random_between(min, max), random_between(min, max)};
}

static Vec3 vec3_unit(Vec3 v) {
  return vec3_scale(v, 1.0f / vec3_length(v));
}

static Vec3 vec3_random_unit(void) {
  while (true) {
    Vec3 p = vec3_random_between(-1.0f, 1.0f);
    float lensq = vec3_length_squared(p);
    if (1e-30f < lensq && lensq <= 1) {
      return vec3_scale(p, 1.0f / sqrtf(lensq));
    }
  }
}

static Vec3 vec3_random_on_hemisphere(Vec3 normal) {
  Vec3 on_unit_sphere = vec3_random_unit();
  if (vec3_dot(on_unit_sphere, normal) > 0.0f) {
    return on_unit_sphere;
  } else {
    return vec3_neg(on_unit_sphere);
  }
}

static Vec3 vec3_reflect(Vec3 v, Vec3 n) {
  Vec3 b = vec3_scale(n, 2.0f * vec3_dot(v, n));
  return vec3_sub(v, b);
}

static Vec3 vec3_lerp(Vec3 a, Vec3 b, float t) {
  return vec3_add(vec3_scale(a, 1.0f - t), vec3_scale(b, t));
}

static void vec3_write(Vec3 v, FILE *f) {
  fprintf(f, "%f %f %f", (double)v.x, (double)v.y, (double)v.z);
}
