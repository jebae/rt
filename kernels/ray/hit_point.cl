t_vec4		hit_point(t_ray *ray, float t)
{
	t_vec4		point;

	point = scalar_mul_vec(t, &(ray->d));
	point = vec_plus_vec(&(ray->e), &point);
	return (point);
}