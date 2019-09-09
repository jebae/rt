void		init_rgb_color(t_vec4 *rgb)
{
	rgb->arr[0] = 0.0f;
	rgb->arr[1] = 0.0f;
	rgb->arr[2] = 0.0f;
	rgb->arr[3] = 1.0f;
}

t_vec4		ray_color(
	t_trace_record *rec,
	t_rt_settings *settings
)
{
	t_object_commons		commons;
	t_vec4					a;
	t_vec4					ds;

	commons = get_object_commons(rec->objects_buf);
	a = ambient(&(settings->i_a), &(commons.color));
	ds = diffuse_specular_per_light(rec, &commons, settings);
	ds = scalar_mul_vec(
		(1.0f - commons.reflectivity) * (1.0f - commons.transparency),
		&ds
	);
	return (vec_plus_vec(&a, &ds));
}

int			ray_trace(
	t_trace_record_queue *rec_queue,
	t_rt_settings *settings
)
{
	t_vec4				rgb;
	t_vec4				shade;
	t_trace_record		*rec;
	t_trace_record		new_rec;

	init_rgb_color(&rgb);
	while (!is_rec_queue_empty(rec_queue))
	{
		rec = pop_rec_queue(rec_queue);
		shade = ray_color(rec, settings);
		shade = scalar_mul_vec(rec->coeff, &shade);
		rgb = vec_plus_vec(&rgb, &shade);
		if (rec->depth >= RT_MAX_DEPTH)
			continue ;
		if (reflect_record(rec, &new_rec, settings))
			push_rec_queue(rec_queue, new_rec);
		if (refract_record(rec, &new_rec, settings))
			push_rec_queue(rec_queue, new_rec);
	}
	return (rgb_to_int(&rgb));
}
