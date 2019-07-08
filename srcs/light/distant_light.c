#include "rt.h"

t_light_wrapper		new_distant_light(
	t_new_light_args *args_light,
	t_new_distant_light_args *args_distant
)
{
	t_light_wrapper		light_wrapper;
	t_distant_light		*light;

	light_wrapper.light = ft_memalloc(sizeof(t_distant_light));
	if (light_wrapper.light == NULL)
		handle_memalloc_err("distant light");
	light = light_wrapper.light;
	light_wrapper.get_light_direction = &distant_light_direction;
	light_wrapper.i_d = args_light->i_d;
	light_wrapper.i_s = args_light->i_s;
	light->d = normalize(&(args_distant->d));
	return (light_wrapper);
}

t_vec4				distant_light_direction(void *light, t_vec4 *point)
{
	t_distant_light		*distant_light;

	point = NULL;
	distant_light = (t_distant_light *)light;
	return (distant_light->d);
}