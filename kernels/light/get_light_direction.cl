t_vec4			get_light_direction(
	__global char *lights_buf,
	t_vec4 *point
)
{
	int			type;
	t_vec4		d;

	type = *((__global int *)lights_buf);
	if (type == RT_LIGHT_TYPE_DISTANT)
		d = distant_light_direction(lights_buf + sizeof(int), point);
	// else if (type == RT_LIGHT_TYPE_SPHERICAL)
	// 	d = spherical_light_direction(lights_buf + sizeof(int), point);
	return (d);
}