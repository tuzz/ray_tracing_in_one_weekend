typedef struct {
  Perlin perlin;
  float scale;
} NoiseTexture;

static Color3 noise_texture_value(NoiseTexture *n, float u, float v, Point3 p) {
  float noise = perlin_noise(&n->perlin, vec3_scale(p, n->scale));
  float normalized = (noise + 1.0f) * 0.5f;

  return vec3_scale(WHITE, normalized);
}
