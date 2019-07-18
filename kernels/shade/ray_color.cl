void		init_rgb_color(t_vec4 *rgb)
{
	rgb->arr[0] = 0.0f;
	rgb->arr[1] = 0.0f;
	rgb->arr[2] = 0.0f;
	rgb->arr[3] = 1.0f;
}

t_vec4		ray_color(
	t_trace_record *rec,
	t_global_settings *settings
)
{
	t_object_commons		commons;
	t_vec4					a;
	t_vec4					ds;

	commons = *(__global t_object_commons *)(rec->objects_buf + sizeof(int));
	a = ambient(&(settings->i_a), &(commons.k_a));
	ds = diffuse_specular_per_light(rec, &commons, settings);
	return (vec_plus_vec(&a, &ds));
}

int			ray_trace(
	t_trace_record_queue *rec_queue,
	t_global_settings *settings
)
{
	t_vec4				rgb;
	t_vec4				shade;
	t_trace_record		rec;

	init_rgb_color(&rgb);
	while (!is_rec_queue_empty(rec_queue))
	{
		// pop -> push reflect and refract
		rec = pop_rec_queue(rec_queue);
		shade = ray_color(&rec, settings);
		rgb = vec_plus_vec(&rgb, &shade);
		// calculate rgb from current surface -> sum
	}
	return (rgb_to_int(&rgb));
}