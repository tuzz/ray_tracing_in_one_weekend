typedef struct {
  Point3 q;
  Vec3 u, v;
  Vec3 w;
  Material *material;
  AABB bbox;
  Vec3 normal;
  float d;
} Quad;

static Quad quad_new(Point3 q, Vec3 u, Vec3 v, Material *material) {
  AABB bbox_diagonal1 = aabb_from_points(q, vec3_add(q, vec3_add(u, v)));
  AABB bbox_diagonal2 = aabb_from_points(vec3_add(q, u), vec3_add(q, v));

  Vec3 n = vec3_cross(u, v);
  Vec3 normal = vec3_unit(n);
  float d = vec3_dot(normal, q);
  Vec3 w = vec3_scale(n, 1.0f / vec3_dot(n, n));

  return (Quad){q, u, v, w, material, aabb_union(&bbox_diagonal1, &bbox_diagonal2), normal, d};
}

static bool quad_is_interior(float a, float b, Hit *hit) {
  static const Interval unit_interval = (Interval){0.0f, 1.0f};

  if (!interval_contains(unit_interval, a) || !interval_contains(unit_interval, b))
    return false;

  hit->u = a;
  hit->v = b;
  return true;
}

static bool quad_hit(const Quad *quad, const Ray3 *ray, Interval ray_t, Hit *hit) {
  float denom = vec3_dot(quad->normal, ray->direction);
  if (fabsf(denom) < 1e-8) return false;

  float t = (quad->d - vec3_dot(quad->normal, ray->origin)) / denom;
  if (!interval_contains(ray_t, t)) return false;

  Point3 intersection = ray3_at(ray, t);
  Vec3 planar_hitpt_vector = vec3_sub(intersection, quad->q);
  float alpha = vec3_dot(quad->w, vec3_cross(planar_hitpt_vector, quad->v));
  float beta = vec3_dot(quad->w, vec3_cross(quad->u, planar_hitpt_vector));

  if (!quad_is_interior(alpha, beta, hit)) return false;

  hit->t = t;
  hit->p = intersection;
  hit->material = quad->material;
  hit_set_face_normal(hit, ray, quad->normal);

  return true;
}
