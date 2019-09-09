__kernel void		intersect_test(
	__global int *out,
	__global char *objects_buf,
	__global char *lights_buf,
	t_rt_settings_args settings_args
)
{
	int					idx = get_global_id(0);
	t_ray				ray;
	t_rt_settings		settings;
	t_trace_record		rec[RT_MAX_RECORD];

	settings = get_rt_settings(objects_buf, lights_buf,
		settings_args.num_objects, settings_args.num_lights, settings_args.i_a);
	ray = ray_origin(
		&(settings_args.ray_grid_props),
		idx % settings_args.window_width, idx / settings_args.window_width);
	if (trace(ray, NULL, rec, &settings))
		out[idx] = 0xFFFFFF;
	else
		out[idx] = 0x0000FF;
}
