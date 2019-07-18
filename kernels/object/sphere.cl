float		get_sphere_t(float d_ce, float d_d, float det)
{
	int			i;
	float		t[2];

	t[0] = (-1.0f * d_ce - sqrt(det)) / d_d;
	t[1] = (-1.0f * d_ce + sqrt(det)) / d_d;
	if (d_d < 0.0f)
		swap_float(&(t[0]), &(t[1]));
	i = 0;
	while (i < 2)
	{
		if (t[i] >= 0.0f)
			return (t[i]);
		i++;
	}
	return (-1.0f);
}

int			sphere_intersect(
	__global char *objects_buf,
	t_ray *ray,
	float *t
)
{
	t_sphere	sphere;
	t_vec4		ce;
	float		d_ce;
	float		d_d;
	float		det;

	sphere = *(__global t_sphere *)objects_buf;
	ce = vec_sub_vec(&(ray->e), &(sphere.c));
	d_ce = vec_dot_vec(&(ray->d), &ce);
	d_d = vec_dot_vec(&(ray->d), &(ray->d));
	det = d_ce * d_ce - d_d * (vec_dot_vec(&ce, &ce) - sphere.r * sphere.r);
	if (det < 0.0f)
		return (RT_FALSE);
	*t = get_sphere_t(d_ce, d_d, det);
	if (*t < 0.0f)
		return (RT_FALSE);
	return (RT_TRUE);
}

t_vec4		sphere_normal(
	__global char *objects_buf,
	t_vec4 *point
)
{
	t_vec4		n;
	t_sphere	sphere;

	sphere = *(__global t_sphere *)objects_buf;
	n = vec_sub_vec(point, &(sphere.c));
	return (normalize_vec(&n));
}