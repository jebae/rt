#include "rt.h"

size_t		new_spherical_light(
	t_light_commons commons,
	t_new_spherical_light_args *args_light,
	char *lights_buf
)
{
	t_spherical_light		light;

	light.commons = commons;
	light.origin = args_light->origin;
	write_mem_buf(lights_buf, (char *)&light, sizeof(light), RT_LIGHT_TYPE_SPHERICAL);
	return (sizeof(light) + sizeof(int));
}