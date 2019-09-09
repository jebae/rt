void			write_record(t_trace_record *rec, float t)
{
	rec->point = hit_point(&(rec->ray), t);
	rec->normal = get_normal(rec->objects_buf, &(rec->point));
	if (vec_dot_vec(&(rec->normal), &(rec->ray.d)) > 0.0f)
		rec->normal = scalar_mul_vec(-1.0f, &(rec->normal));
}

int				trace(
	t_ray ray,
	t_trace_record *prev_rec,
	t_trace_record *rec,
	t_rt_settings *settings
)
{
	int					i;
	float				t[2];
	size_t				stride;
	__global char		*objects_ptr;

	t[1] = INFINITY;
	objects_ptr = settings->objects_buf;
	stride = 0;
	i = -1;
	while (++i < settings->num_objects && (objects_ptr += stride))
	{
		stride = get_object_stride(objects_ptr);
		if (!intersect(objects_ptr, &ray, &(t[0])))
			continue ;
		if (t[0] > t[1])
			continue ;
		t[1] = t[0];
		rec->objects_buf = objects_ptr;
	}
	if (t[1] == INFINITY)
		return (RT_FALSE);
	rec->ray = ray;
	rec->prev = prev_rec;
	write_record(rec, t[1]);
	return (RT_TRUE);
}
