t_vec4		distant_light_direction(
	__global char *lights_buf,
	t_vec4 *point
)
{
	t_distant_light		light;

	light = *(__global t_distant_light *)lights_buf;
	return (light.d);
}