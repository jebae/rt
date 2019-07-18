__kernel void		intersect_test(
	__global int *out,
	__global char *objects_buf,
	__global char *lights_buf,
	t_ray_grid_properties ray_grid_props,
	int num_objects,
	int num_lights,
	t_vec4 i_a,
	int width
)
{
	int					idx = get_global_id(0);
	t_ray				ray;
	t_global_settings	settings;
	t_trace_record		rec[RT_MAX_RECORD];

	settings = get_global_settings(objects_buf, lights_buf,
		num_objects, num_lights, i_a);
	ray = ray_origin(&ray_grid_props, idx % width, idx / width);
	if (trace(ray, NULL, rec, &settings))
		out[idx] = 0xFFFFFF;
	else
		out[idx] = 0x0000FF;
}
