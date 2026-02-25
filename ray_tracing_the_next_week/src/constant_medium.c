struct ConstantMedium {
  Hittable *boundary;
  float neg_inv_density;
  Material *phase_function;
};

static ConstantMedium constant_medium_new(Hittable *boundary, float density, Material *isotropic) {
  return (ConstantMedium){boundary, -1.0f / density, isotropic};
}

static bool constant_medium_hit(const ConstantMedium *m, const Ray3 *ray, Interval ray_t, Hit *hit) {
  Hit hit1, hit2;

  // Return false if the ray did not hit the front of the boundary.
  // Check the full line, rather than just the ray because we might already be in the medium.
  if (!hittable_hit(m->boundary, ray, INTERVAL_UNIVERSE, &hit1))
    return false;

  // Return false if the ray did not hit the back of the boundary.
  // Check from the point immediately after we entered the boundary (+0.0001f).
  if (!hittable_hit(m->boundary, ray, interval_from(hit1.t + 0.0001f, FLT_MAX), &hit2))
    return false;

  // Note: the implemenation above only works for the first entry/exit point of
  // the shape. If the ray enters again, which might happen for concave shapes,
  // the hits are ignored. We'd need to keep iterating the process above and
  // update t each time to detect these additional hits.

  // Clamp the hit position to ray_t which is the line segment we care about.
  // e.g. if the ray hit the medium before ray_t then start it from ray_t.
  if (hit1.t < ray_t.min) hit1.t = ray_t.min;
  if (hit2.t > ray_t.max) hit2.t = ray_t.max;

  // Return false if that now means the ray didn't hit any part of the medium.
  if (hit1.t >= hit2.t)
    return false;

  if (hit1.t < 0.0f)
    hit1.t = 0.0f;

  // Probabilistically calculate the distance where the ray hit within the
  // medium based on how far the ray would travel until it exits the medium.
  float ray_length = vec3_length(ray->direction);
  float distance_inside_boundary = (hit2.t - hit1.t) * ray_length;
  float hit_distance = m->neg_inv_density * logf(random_float());

  // If it wouldn't have hit until after it exited then no hit occurred.
  if (hit_distance > distance_inside_boundary)
    return false;

  hit->t = hit1.t + hit_distance / ray_length;
  hit->p = ray3_at(ray, hit->t);

  hit->normal = (Vec3){{1.0f, 0.0f, 0.0f}}; // Not used by isotropic material.
  hit->front_face = true;                   // Not used by isotropic material.
  hit->material = m->phase_function;

  return true;
}

static AABB constant_medium_bounding_box(const ConstantMedium *m) {
  return hittable_bounding_box(m->boundary);
}
