float			get_ior(t_trace_record *rec)
{
	int					refract_count;
	t_ray				*recent_enter_ray;
	t_trace_record		*cur;
	t_trace_record		*prev;

	refract_count = 0;
	recent_enter_ray = NULL;
	cur = rec;
	prev = rec->prev;
	while (prev != NULL)
	{
		if (cur->ray.type == RT_RAY_TYPE_REFRACTION &&
			prev->objects_buf == rec->objects_buf)
		{
			if (recent_enter_ray == NULL)
				recent_enter_ray = &(cur->ray);
			refract_count++;
		}
		cur = prev;
		prev = prev->prev;
	}
	if (refract_count % 2 == 0)
		return (get_object_ior(rec->objects_buf));
	return (recent_enter_ray->ior_medium);
}

t_ray	get_refract_ray(t_trace_record *rec)
{
	float			snell_ratio;
	float			d_n;
	float			det;
	t_vec4			v;
	t_ray			refract_ray;

	refract_ray.ior_medium = get_ior(rec);
	snell_ratio = rec->ray.ior_medium / refract_ray.ior_medium;
	d_n = -1.0f * vec_dot_vec(&(rec->ray.d), &(rec->normal));
	det = 1 - snell_ratio * snell_ratio * (1 - d_n * d_n);
	if (det < 0.0f)
	{
		refract_ray.type = RT_RAY_TYPE_NONE;
		return (refract_ray);
	}
	v = scalar_mul_vec(snell_ratio, &(rec->ray.d));
	refract_ray.d = scalar_mul_vec(snell_ratio * d_n - sqrt(det), &(rec->normal));
	refract_ray.d = vec_plus_vec(&v, &(refract_ray.d));
	refract_ray.e = scalar_mul_vec(-1.0f * RT_BIAS, &(rec->normal));
	refract_ray.e = vec_plus_vec(&(rec->point), &(refract_ray.e));
	refract_ray.type = RT_RAY_TYPE_REFRACTION;
	return (refract_ray);
}

int					refract_record(
	t_trace_record *prev,
	t_trace_record *cur,
	t_global_settings *settings
)
{
	t_ray				ray;
	t_object_commons	commons;

	ray = get_refract_ray(prev);
	if (trace(ray, prev, cur, settings))
	{
		commons = get_object_commons(prev->objects_buf);
		cur->coeff = prev->coeff * (1.0f - commons.reflectivity) * commons.transparency;
		if (cur->coeff == 0.0f)
			return (RT_FALSE);
		cur->depth = prev->depth + 1;
		return (RT_TRUE);
	}
	return (RT_FALSE);
}
