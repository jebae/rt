t_ray				get_reflect_ray(t_trace_record *rec)
{
	float		n_ray;
	t_ray		reflect_ray;

	n_ray = -1.0f * vec_dot_vec(&(rec->normal), &(rec->ray.d));
	reflect_ray.d = scalar_mul_vec(2.0f * n_ray, &(rec->normal));
	reflect_ray.d = vec_plus_vec(&(rec->ray.d), &(reflect_ray.d));
	reflect_ray.e = scalar_mul_vec(RT_BIAS, &(rec->normal));
	reflect_ray.e = vec_plus_vec(&(rec->point), &(reflect_ray.e));
	reflect_ray.ior_medium = rec->ray.ior_medium;
	reflect_ray.type = RT_RAY_TYPE_REFLECTION;
	return (reflect_ray);
}

int					reflect_record(
	t_trace_record *prev,
	t_trace_record *cur,
	t_global_settings *settings
)
{
	t_ray				ray;
	t_object_commons	commons;

	ray = get_reflect_ray(prev);
	if (trace(ray, prev, cur, settings))
	{
		commons = get_object_commons(prev->objects_buf);
		cur->coeff = prev->coeff * commons.reflectivity;
		if (cur->coeff == 0.0f)
			return (RT_FALSE);
		cur->depth = prev->depth + 1;
		return (RT_TRUE);
	}
	return (RT_FALSE);
}
