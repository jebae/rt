t_light_attr			get_light_attr(
	__global char *lights_buf,
	t_vec4 *point
)
{
	int				type;
	t_light_attr	attr;

	type = *((__global int *)lights_buf);
	if (type == RT_LIGHT_TYPE_DISTANT)
		attr = distant_light_attr(lights_buf + sizeof(int), point);
	else if (type == RT_LIGHT_TYPE_SPHERICAL)
		attr = spherical_light_attr(lights_buf + sizeof(int), point);
	return (attr);
}