t_cylinder_intersect_coefficients		get_cylinder_intersect_coefficients(
	t_cylinder *cylinder,
	t_ray *ray
)
{
	t_cylinder_intersect_coefficients		coeff;
	t_vec4									a;
	t_vec4									b;

	a = scalar_mul_vec(
		vec_dot_vec(&(ray->d), &(cylinder->v)), &(cylinder->v));
	a = vec_sub_vec(&(ray->d), &a);
	b = vec_sub_vec(&(cylinder->c), &(ray->e));
	b = scalar_mul_vec(
		vec_dot_vec(&b, &(cylinder->v)), &(cylinder->v));
	b = vec_sub_vec(&b, &(cylinder->c));
	b = vec_plus_vec(&(ray->e), &b);
	coeff.a = vec_dot_vec(&a, &a);
	coeff.b = vec_dot_vec(&a, &b);
	coeff.c = vec_dot_vec(&b, &b) - cylinder->r * cylinder->r;
	return (coeff);
}

float									get_cylinder_t(
	t_cylinder_intersect_coefficients *coeff,
	float det,
	t_cylinder *cylinder,
	t_ray *ray
)
{
	int			i;
	float		t[2];
	t_vec4		cp;

	t[0] = (-1.0f * coeff->b - sqrt(det)) / coeff->a;
	t[1] = (-1.0f * coeff->b + sqrt(det)) / coeff->a;
	if (coeff->a < 0.0f)
		swap_float(&(t[0]), &(t[1]));
	i = 0;
	while (i < 2)
	{
		if (t[i] >= 0.0f)
		{
			cp = hit_point(ray, t[i]);
			cp = vec_sub_vec(&cp, &(cylinder->c));
			det = vec_dot_vec(&cp, &(cylinder->v));
			if (det >= 0.0f && det <= cylinder->h)
				return (t[i]);
		}
		i++;
	}
	return (-1.0f);
}

int										cylinder_intersect(
	__global char *objects_buf,
	t_ray *ray,
	float *t
)
{
	t_cylinder								cylinder;
	t_cylinder_intersect_coefficients		coeff;
	float									det;

	cylinder = *(__global t_cylinder *)objects_buf;
	coeff = get_cylinder_intersect_coefficients(&cylinder, ray);
	det = coeff.b * coeff.b - coeff.a * coeff.c;
	if (det < 0.0f)
		return (RT_FALSE);
	*t = get_cylinder_t(&coeff, det, &cylinder, ray);
	if (*t < 0.0f)
		return (RT_FALSE);
	return (RT_TRUE);
}

t_vec4			cylinder_normal(
	__global char *objects_buf,
	t_vec4 *point
)
{
	t_cylinder		cylinder;
	t_vec4			cp;
	t_vec4			n;

	cylinder = *(__global t_cylinder *)objects_buf;
	cp = vec_sub_vec(point, &(cylinder.c));
	n = scalar_mul_vec(vec_dot_vec(&cp, &(cylinder.v)), &(cylinder.v));
	n = vec_sub_vec(&cp, &n);
	return (normalize_vec(&n));
}