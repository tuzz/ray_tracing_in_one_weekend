typedef struct {
  float x;
  float y;
  float z;
} Vec3;

static Vec3 vec3_negate(Vec3 self) {
  return (Vec3){
    .x = -self.x,
    .y = -self.y,
    .z = -self.z,
  };
}

static Vec3 vec3_add(Vec3 self, Vec3 other) {
  return (Vec3){
    .x = self.x + other.x,
    .y = self.y + other.y,
    .z = self.z + other.z,
  };
}

static Vec3 vec3_subtract(Vec3 self, Vec3 other) {
  return (Vec3){
    .x = self.x - other.x,
    .y = self.y - other.y,
    .z = self.z - other.z,
  };
}

static Vec3 vec3_multiply(Vec3 self, Vec3 other) {
  return (Vec3){
    .x = self.x * other.x,
    .y = self.y * other.y,
    .z = self.z * other.z,
  };
}

static Vec3 vec3_scale(Vec3 self, float amount) {
  return (Vec3){
    .x = self.x * amount,
    .y = self.y * amount,
    .z = self.z * amount,
  };
}

static float vec3_dot(Vec3 self, Vec3 other) {
  return (self.x * other.x) + (self.y * other.y) + (self.z * other.z);
}

static Vec3 vec3_cross(Vec3 self, Vec3 other) {
  return (Vec3){
    .x = (self.y * other.z) - (self.z * other.y),
    .y = (self.z * other.x) - (self.x * other.z),
    .z = (self.x * other.y) - (self.y * other.x),
  };
}

static float vec3_length_squared(Vec3 self) {
  return (self.x * self.x) + (self.y * self.y) + (self.z * self.z);
}

static float vec3_length(Vec3 self) {
  return sqrtf(vec3_length_squared(self));
}

static Vec3 vec3_unit(Vec3 self) {
  return vec3_scale(self, 1.0f / vec3_length(self));
}

static void vec3_write(Vec3 self, FILE *stream) {
  fprintf(stream, "%f %f %f", (double)self.x, (double)self.y, (double)self.z);
}
