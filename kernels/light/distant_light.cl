t_light_attr		distant_light_attr(
	__global char *lights_buf,
	t_vec4 *point
)
{
	t_distant_light		light;
	t_light_attr		attr;

	light = *(__global t_distant_light *)lights_buf;
	attr.direction = light.d;
	attr.intensity = light.commons.intensity;
	attr.dist = INFINITY;
	return (attr);
}