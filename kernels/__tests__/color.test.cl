__kernel void		color_test(
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
	int						idx = get_global_id(0);
	t_ray					ray;
	t_global_settings		settings;
	t_trace_record			rec;
	t_trace_record_queue	rec_queue;

	settings = get_global_settings(objects_buf, lights_buf,
		num_objects, num_lights, i_a);
	ray = ray_origin(&ray_grid_props, idx % width, idx / width);
	if (trace(ray, NULL, &rec, &settings))
	{
		init_rec_queue(&rec_queue);
		push_rec_queue(&rec_queue, rec);
		out[idx] = ray_trace(&rec_queue, &settings);
		return ;
	}
	out[idx] = RT_BACKGROUND_COLOR;
}
