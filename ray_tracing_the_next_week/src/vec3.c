typedef union {
  float coords[3];
  struct { float x, y, z; } coord;
} Vec3;

static Vec3 vec3_neg(Vec3 v) {
  return (Vec3){{-v.coord.x, -v.coord.y, -v.coord.z}};
}

static Vec3 vec3_add(Vec3 a, Vec3 b) {
  return (Vec3){{a.coord.x + b.coord.x, a.coord.y + b.coord.y, a.coord.z + b.coord.z}};
}

static Vec3 vec3_sub(Vec3 a, Vec3 b) {
  return (Vec3){{a.coord.x - b.coord.x, a.coord.y - b.coord.y, a.coord.z - b.coord.z}};
}

static Vec3 vec3_mul(Vec3 a, Vec3 b) {
  return (Vec3){{a.coord.x * b.coord.x, a.coord.y * b.coord.y, a.coord.z * b.coord.z}};
}

static Vec3 vec3_scale(Vec3 v, float s) {
  return (Vec3){{v.coord.x * s, v.coord.y * s, v.coord.z * s}};
}

static float vec3_dot(Vec3 a, Vec3 b) {
  return a.coord.x * b.coord.x + a.coord.y * b.coord.y + a.coord.z * b.coord.z;
}

static Vec3 vec3_cross(Vec3 a, Vec3 b) {
  return (Vec3){{
    a.coord.y * b.coord.z - a.coord.z * b.coord.y,
    a.coord.z * b.coord.x - a.coord.x * b.coord.z,
    a.coord.x * b.coord.y - a.coord.y * b.coord.x,
  }};
}

static float vec3_length_squared(Vec3 v) {
  return v.coord.x * v.coord.x + v.coord.y * v.coord.y + v.coord.z * v.coord.z;
}

static float vec3_length(Vec3 v) {
  return sqrtf(vec3_length_squared(v));
}

static bool vec3_near_zero(Vec3 v) {
  return fabsf(v.coord.x) < 1e-8f && fabsf(v.coord.y) < 1e-8f && fabsf(v.coord.z) < 1e-8f;
}

static Vec3 vec3_random(void) {
  return (Vec3){{random_float(), random_float(), random_float()}};
}

static Vec3 vec3_random_between(float min, float max) {
  return (Vec3){{random_between(min, max), random_between(min, max), random_between(min, max)}};
}

static Vec3 vec3_unit(Vec3 v) {
  return vec3_scale(v, 1.0f / vec3_length(v));
}

static Vec3 vec3_random_in_unit_disk(void) {
  while (true) {
    Vec3 p = (Vec3){{random_between(-1.0f, 1.0f), random_between(-1.0f, 1.0f), 0.0f}};
    if (vec3_length_squared(p) < 1.0f) return p;
  }
}

static Vec3 vec3_random_unit(void) {
  while (true) {
    Vec3 p = vec3_random_between(-1.0f, 1.0f);
    float lensq = vec3_length_squared(p);
    if (1e-30f < lensq && lensq <= 1.0f) {
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

static Vec3 vec3_refract(Vec3 uv, Vec3 n, float etai_over_etat) {
  float cos_theta = fminf(vec3_dot(vec3_neg(uv), n), 1.0f);
  Vec3 r_out_perp = vec3_scale(vec3_add(uv, vec3_scale(n, cos_theta)), etai_over_etat);
  Vec3 r_out_parallel = vec3_scale(n, -sqrtf(fabsf(1.0f - vec3_length_squared(r_out_perp))));
  return vec3_add(r_out_perp, r_out_parallel);
}

static Vec3 vec3_lerp(Vec3 a, Vec3 b, float t) {
  return vec3_add(vec3_scale(a, 1.0f - t), vec3_scale(b, t));
}

static void vec3_write(Vec3 v, FILE *f) {
  fprintf(f, "%f %f %f", (double)v.coord.x, (double)v.coord.y, (double)v.coord.z);
}
