typedef struct {
  Perlin perlin;
  float scale;
} NoiseTexture;

static Color3 noise_texture_value(NoiseTexture *n, float u, float v, Point3 p) {
  float turbulence = perlin_turbulence(&n->perlin, p, 7);
  float theta = n->scale * p.coord.z + 10.0f * turbulence;

  return vec3_scale(GREY, 1.0f + sinf(theta));
}
