typedef struct {
  Point3 origin;
  Vec3 direction;
} Ray3;

static Point3 ray3_at(Ray3 self, float t) {
  return vec3_add(self.origin, vec3_scale(self.direction, t));
}

static Color3 ray3_color(Ray3 self) {
  Vec3 unit_direction = vec3_unit(self.direction);
  float alpha = 0.5f * (unit_direction.y + 1.0f);

  Color3 white = { 1.0f, 1.0f, 1.0f };
  Color3 sky_blue = { 0.5f, 0.7f, 1.0f };

  return vec3_lerp(white, sky_blue, alpha);
}
