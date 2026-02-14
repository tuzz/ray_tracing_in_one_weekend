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

static Vec3 vec3_unit(Vec3 v) {
  return vec3_scale(v, 1.0f / vec3_length(v));
}

static Vec3 vec3_lerp(Vec3 a, Vec3 b, float t) {
  return vec3_add(vec3_scale(a, 1.0f - t), vec3_scale(b, t));
}

static void vec3_write(Vec3 v, FILE *f) {
  fprintf(f, "%f %f %f", (double)v.x, (double)v.y, (double)v.z);
}
