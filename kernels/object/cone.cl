t_cone_intersect_coefficients		get_cone_intersect_coefficients(
	t_cone *cone,
	t_ray *ray
)
{
	float								ce_v;
	float								d_v;
	t_vec4								ce;
	t_cone_intersect_coefficients		coeffs;

	ce = vec_sub_vec(&(ray->e), &(cone->c));
	ce_v = vec_dot_vec(&ce, &(cone->v));
	d_v = vec_dot_vec(&(ray->d), &(cone->v));
	coeffs.a = d_v * d_v - cone->cos_2_theta;
	coeffs.b = ce_v * d_v - vec_dot_vec(&(ray->d), &ce) * cone->cos_2_theta;
	coeffs.c = ce_v * ce_v - vec_dot_vec(&ce, &ce) * cone->cos_2_theta;
	return (coeffs);
}

float								get_cone_t(
	t_cone_intersect_coefficients *coeffs,
	float det,
	t_cone *cone,
	t_ray *ray
)
{
	int			i;
	float		t[2];
	t_vec4		cp;

	t[0] = (-1.0f * coeffs->b - sqrt(det)) / coeffs->a;
	t[1] = (-1.0f * coeffs->b + sqrt(det)) / coeffs->a;
	if (coeffs->a < 0.0f)
		swap_float(&(t[0]), &(t[1]));
	i = 0;
	while (i < 2)
	{
		if (t[i] >= 0.0f)
		{
			cp = hit_point(ray, t[i]);
			cp = vec_sub_vec(&cp, &(cone->c));
			det = vec_dot_vec(&cp, &(cone->v));
			if (det >= 0.0f && det <= cone->h)
				return (t[i]);
		}
		i++;
	}
	return (-1.0f);
}

int									cone_intersect(
	__global char *objects_buf,
	t_ray *ray,
	float *t
)
{
	t_cone							cone;
	float							det;
	t_cone_intersect_coefficients	coeffs;

	cone = *(__global t_cone *)objects_buf;
	coeffs = get_cone_intersect_coefficients(&cone, ray);
	det = coeffs.b * coeffs.b - coeffs.a * coeffs.c;
	if (det < 0.0f)
		return (RT_FALSE);
	*t = get_cone_t(&coeffs, det, &cone, ray);
	if (*t < 0.0f)
		return (RT_FALSE);
	return (RT_TRUE);
}

t_vec4								cone_normal(
	__global char *objects_buf,
	t_vec4 *point
)
{
	t_cone		cone;
	float		k;
	t_vec4		cp;
	t_vec4		n;

	cone = *(__global t_cone *)objects_buf;
	cp = vec_sub_vec(point, &(cone.c));
	k = vec_dot_vec(&cp, &cp) / vec_dot_vec(&(cone.v), &cp);
	n = scalar_mul_vec(k, &(cone.v));
	n = vec_sub_vec(&cp, &n);
	return (normalize_vec(&n));
}