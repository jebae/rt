__kernel void		intersect_test(
	__global int *out,
	__global char *objects_buf,
	t_ray_grid_properties ray_grid_props,
	int num_objects,
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
		out[idx] = 0xFFFFFF;
	}
	else
		out[idx] = 0x0000FF;
}
