typedef enum {
  MATERIAL_LAMBERTIAN,
  MATERIAL_METAL,
  MATERIAL_DIELECTRIC,
} MaterialType;

struct Material {
  MaterialType type;
  union {
    Lambertian lambertian;
    Metal metal;
    Dielectric dielectric;
  } u;
};

static bool material_scatter(const Material *m, const Ray3 *ray, const Hit *hit, Color3 *attentuation, Ray3 *scattered) {
  switch (m->type){
    // hello
    case MATERIAL_LAMBERTIAN:
      return lambertian_scatter(&m->u.lambertian, ray, hit, attentuation, scattered);
    case MATERIAL_METAL: // modified
      return metal_scatter(&m->u.metal, ray, hit, attentuation, scattered);
    case MATERIAL_DIELECTRIC:
      return dielectric_scatter(&m->u.dielectric, ray, hit, attentuation, scattered);
    default:
      assert(false && "Unknown Material");
  }
}
