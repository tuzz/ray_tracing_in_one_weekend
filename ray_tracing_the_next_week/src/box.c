static HittableList box_new(Point3 a, Point3 b, Material *material) {
  HittableList sides = hittable_list_new();

  Point3 min = vec3_min(a, b);
  Point3 max = vec3_max(a, b);

  Vec3 dx = (Vec3){{max.coord.x - min.coord.x, 0.0f, 0.0f}};
  Vec3 dy = (Vec3){{0.0f, max.coord.y - min.coord.y, 0.0f}};
  Vec3 dz = (Vec3){{0.0f, 0.0f, max.coord.z - min.coord.z}};

  hittable_list_add(&sides, (Hittable){.type = HITTABLE_QUAD, .u.quad = quad_new((Point3){{min.coord.x, min.coord.y, max.coord.z}}, dx, dy, material)});
  hittable_list_add(&sides, (Hittable){.type = HITTABLE_QUAD, .u.quad = quad_new((Point3){{max.coord.x, min.coord.y, max.coord.z}}, vec3_neg(dz), dy, material)});
  hittable_list_add(&sides, (Hittable){.type = HITTABLE_QUAD, .u.quad = quad_new((Point3){{max.coord.x, min.coord.y, min.coord.z}}, vec3_neg(dx), dy, material)});
  hittable_list_add(&sides, (Hittable){.type = HITTABLE_QUAD, .u.quad = quad_new((Point3){{min.coord.x, min.coord.y, min.coord.z}}, dz, dy, material)});
  hittable_list_add(&sides, (Hittable){.type = HITTABLE_QUAD, .u.quad = quad_new((Point3){{min.coord.x, max.coord.y, max.coord.z}}, dx, vec3_neg(dz), material)});
  hittable_list_add(&sides, (Hittable){.type = HITTABLE_QUAD, .u.quad = quad_new((Point3){{min.coord.x, min.coord.y, min.coord.z}}, dx, vec3_neg(dz), material)});

  return sides;
}
