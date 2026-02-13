#include <math.h>

typedef struct {
  float x;
  float y;
  float z;
} Vector3f;

static Vector3f vector3f_negate(const Vector3f *self) {
  return (Vector3f){
    .x = -self->x,
    .y = -self->y,
    .z = -self->z,
  };
}

static Vector3f vector3f_add(const Vector3f *self, const Vector3f *other) {
  return (Vector3f){
    .x = self->x + other->x,
    .y = self->y + other->y,
    .z = self->z + other->z,
  };
}

static Vector3f vector3f_subtract(const Vector3f *self, const Vector3f *other) {
  return (Vector3f){
    .x = self->x - other->x,
    .y = self->y - other->y,
    .z = self->z - other->z,
  };
}

static Vector3f vector3f_multiply(const Vector3f *self, const Vector3f *other) {
  return (Vector3f){
    .x = self->x * other->x,
    .y = self->y * other->y,
    .z = self->z * other->z,
  };
}

static Vector3f vector3f_scale(const Vector3f *self, float amount) {
  return (Vector3f){
    .x = self->x * amount,
    .y = self->y * amount,
    .z = self->z * amount,
  };
}

static float vector3f_dot(const Vector3f *self, const Vector3f *other) {
  return (self->x * other->x) + (self->y * other->y) + (self->z * other->z);
}

static Vector3f vector3f_cross(const Vector3f *self, const Vector3f *other) {
  return (Vector3f){
    .x = (self->y * other->z) - (self->z * other->y),
    .y = (self->z * other->x) - (self->x * other->z),
    .z = (self->x * other->y) - (self->y * other->x),
  };
}

static float vector3f_length_squared(const Vector3f *self) {
  return (self->x * self->x) + (self->y * self->y) + (self->z * self->z);
}

static float vector3f_length(const Vector3f *self) {
  return sqrtf(vector3f_length_squared(self));
}

static Vector3f vector3f_unit(const Vector3f *self) {
  return vector3f_scale(self, 1.0f / vector3f_length(self));
}

static void vector3f_print(const Vector3f *self, FILE *stream) {
  fprintf(stream, "%f %f %f", (double)self->x, (double)self->y, (double)self->z);
}
