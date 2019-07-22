size_t		get_light_stride(__global char *lights_buf)
{
	int		type;

	type = *(__global int *)lights_buf;
	if (type == RT_LIGHT_TYPE_DISTANT)
		return (sizeof(t_distant_light) + sizeof(int));
	else if (type == RT_LIGHT_TYPE_SPHERICAL)
		return (sizeof(t_spherical_light) + sizeof(int));
	return (0);
}