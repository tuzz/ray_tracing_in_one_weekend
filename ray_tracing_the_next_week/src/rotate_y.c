struct RotateY {
  Hittable *hittable;
  float sin_theta;
  float cos_theta;
  AABB bbox;
};

static RotateY rotate_y_new(Hittable *hittable, float angle) {
  float radians = degrees_to_radians(angle);
  float sin_theta = sinf(radians);
  float cos_theta = cosf(radians);
  AABB bbox = hittable_bounding_box(hittable);

  Point3 min = {{FLT_MAX, FLT_MAX, FLT_MAX}};
  Point3 max = {{-FLT_MAX, -FLT_MAX, -FLT_MAX}};

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {
        float x = i * bbox.interval.x.max + (1 - i) * bbox.interval.x.min;
        float y = j * bbox.interval.y.max + (1 - j) * bbox.interval.y.min;
        float z = k * bbox.interval.z.max + (1 - k) * bbox.interval.z.min;

        float newx = cos_theta * x + sin_theta * z;
        float newz = -sin_theta * x + cos_theta * z;

        Vec3 tester = {{newx, y, newz}};

        for (int c = 0; c < 3; c++) {
          min.coords[c] = fminf(min.coords[c], tester.coords[c]);
          max.coords[c] = fmaxf(max.coords[c], tester.coords[c]);
        }
      }
    }
  }

  return (RotateY){hittable, sin_theta, cos_theta, aabb_from_points(min, max)};
}

static bool rotate_y_hit(const RotateY *r, const Ray3 *ray, Interval ray_t, Hit *hit) {
  Point3 origin = {{
    r->cos_theta * ray->origin.coord.x - r->sin_theta * ray->origin.coord.z,
    ray->origin.coord.y,
    r->sin_theta * ray->origin.coord.x + r->cos_theta * ray->origin.coord.z,
  }};

  Vec3 direction = {{
    r->cos_theta * ray->direction.coord.x - r->sin_theta * ray->direction.coord.z,
    ray->direction.coord.y,
    r->sin_theta * ray->direction.coord.x + r->cos_theta * ray->direction.coord.z,
  }};

  Ray3 rotated_r = {.origin = origin, .direction = direction, .time = ray->time};

  if (!hittable_hit(r->hittable, &rotated_r, ray_t, hit)) return false;

  hit->p = (Point3){{
    r->cos_theta * hit->p.coord.x + r->sin_theta * hit->p.coord.z,
    hit->p.coord.y,
    -r->sin_theta * hit->p.coord.x + r->cos_theta * hit->p.coord.z,
  }};

  hit->normal = (Vec3){{
    r->cos_theta * hit->normal.coord.x + r->sin_theta * hit->normal.coord.z,
    hit->normal.coord.y,
    -r->sin_theta * hit->normal.coord.x + r->cos_theta * hit->normal.coord.z,
  }};

  return true;
}

static AABB rotate_y_bounding_box(const RotateY *r) {
  return r->bbox;
}
