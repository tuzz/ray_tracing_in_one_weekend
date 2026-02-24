typedef struct {
  Perlin perlin;
  float scale;
} NoiseTexture;

static Color3 noise_texture_value(NoiseTexture *n, float u, float v, Point3 p) {
  return vec3_scale(WHITE, perlin_turbulence(&n->perlin, p, 7));
}
