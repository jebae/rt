__kernel void		ray_trace(
	__global int *out,
	__global char *objects_buf,
	__global char *lights_buf,
	t_ray_grid_properties ray_grid_props,
	int num_objects,
	int num_lights,
	int width
)
{
	int					idx = get_global_id(0);
	t_ray				ray;
	t_global_settings	settings;
	t_trace_record		rec[RT_MAX_RECORD];

	set_global_settings(&settings, objects_buf, num_objects);
	ray = ray_origin(&ray_grid_props, idx % width, idx / width);
	if (trace(ray, NULL, rec, &settings))
	{
		// init_queue_with rec
		// looping pop and push
		out[idx] = 0xFFFFFF;
	}
	out[idx] = 0x000000;
}
