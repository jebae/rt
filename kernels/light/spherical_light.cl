t_light_attr		spherical_light_attr(
	__global char *lights_buf,
	t_vec4 *point
)
{
	t_spherical_light		light;
	t_light_attr			attr;

	light = *(__global t_spherical_light *)lights_buf;
	attr.direction = vec_sub_vec(point, &(light.origin));
	attr.dist = vec_norm(&(attr.direction));
	attr.intensity = scalar_mul_vec(
		1.0f / (4.0f * M_PI * attr.dist * attr.dist), &(light.commons.intensity));
	attr.direction = scalar_mul_vec(1.0f / attr.dist, &(attr.direction));
	return (attr);
}