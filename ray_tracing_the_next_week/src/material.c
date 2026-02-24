typedef enum {
  MATERIAL_LAMBERTIAN,
  MATERIAL_METAL,
  MATERIAL_DIELECTRIC,
  MATERIAL_DIFFUSE_LIGHT,
} MaterialType;

struct Material {
  MaterialType type;
  union {
    Lambertian lambertian;
    Metal metal;
    Dielectric dielectric;
    DiffuseLight diffuse_light;
  } u;
};

static Color3 material_emitted(const Material *m, float u, float v, Point3 p) {
  switch (m->type){
    case MATERIAL_LAMBERTIAN:
    case MATERIAL_METAL:
    case MATERIAL_DIELECTRIC:
      return BLACK;
    case MATERIAL_DIFFUSE_LIGHT:
      return diffuse_light_emitted(&m->u.diffuse_light, u, v, p);
    default:
      assert(false && "Unknown Material");
  }
}

static bool material_scatter(const Material *m, const Ray3 *ray, const Hit *hit, Color3 *attentuation, Ray3 *scattered) {
  switch (m->type){
    case MATERIAL_LAMBERTIAN:
      return lambertian_scatter(&m->u.lambertian, ray, hit, attentuation, scattered);
    case MATERIAL_METAL:
      return metal_scatter(&m->u.metal, ray, hit, attentuation, scattered);
    case MATERIAL_DIELECTRIC:
      return dielectric_scatter(&m->u.dielectric, ray, hit, attentuation, scattered);
    case MATERIAL_DIFFUSE_LIGHT:
      return false;
    default:
      assert(false && "Unknown Material");
  }
}
