typedef enum {
  MATERIAL_LAMBERTIAN,
} MaterialType;

struct Material {
  MaterialType type;
  union {
    Lambertian lambertian;
  } u;
};

static bool material_scatter(const Material *m, const Ray3 *ray, const Hit *hit, Color3 *attentuation, Ray3 *scattered) {
  switch (m->type){
    case MATERIAL_LAMBERTIAN:
      return lambertian_scatter(&m->u.lambertian, ray, hit, attentuation, scattered);
    default:
      assert(false && "Unknown Material");
  }
}
