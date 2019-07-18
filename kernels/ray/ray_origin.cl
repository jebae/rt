t_ray		ray_origin(
	t_ray_grid_properties *props,
	int scalar_x,
	int scalar_y
)
{
	t_ray		ray;
	t_vec4		d;
	t_vec4		v;

	v = scalar_mul_vec((float)scalar_x, &(props->dx));
	d = vec_plus_vec(&(props->offset), &v);
	v = scalar_mul_vec((float)scalar_y, &(props->dy));
	d = vec_plus_vec(&d, &v);
	ray.d = normalize_vec(&d);
	ray.e = props->e;
	return (ray);
}