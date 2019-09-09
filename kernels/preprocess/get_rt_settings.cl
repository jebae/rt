t_rt_settings	get_rt_settings(
	__global char *objects_buf,
	__global char *lights_buf,
	int num_objects,
	int num_lights,
	t_vec4 i_a
)
{
	t_rt_settings		settings;

	settings.objects_buf = objects_buf;
	settings.lights_buf = lights_buf;
	settings.num_objects = num_objects;
	settings.num_lights = num_lights;
	settings.i_a = i_a;
	return (settings);
}
