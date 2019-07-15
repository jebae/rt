#include "rt.h"

static t_vec4		cal_color(
	t_object_wrapper *object_wrapper,
	t_vec4 *rgb_shades
)
{
	int					i;
	t_vec4				res;

	rgb_shades[AMBIENT] = scalar_mul_vec(
		(1.0f - object_wrapper->reflectivity) * (1.0f - object_wrapper->transparency),
		&(rgb_shades[AMBIENT]));
	rgb_shades[DIFFUSE] = scalar_mul_vec(
		(1.0f - object_wrapper->reflectivity) * (1.0f - object_wrapper->transparency),
		&(rgb_shades[DIFFUSE]));
	rgb_shades[REFLECT] = scalar_mul_vec(
		object_wrapper->reflectivity, &(rgb_shades[REFLECT]));
	rgb_shades[REFRACT] = scalar_mul_vec(
		(1.0f - object_wrapper->reflectivity) * object_wrapper->transparency,
		&(rgb_shades[REFRACT]));
	res = (t_vec4){{0.0f, 0.0f, 0.0f, 1.0f}};
	i = 0;
	while (i < 5)
	{
		res = vec_plus_vec(&(rgb_shades[i]), &res);
		i++;
	}
	return (res);
}

static void			diffuse_specular_per_light(
	t_trace_record *rec,
	t_global_rt_args *args,
	t_vec4 *rgb_shades
)
{
	int			i;
	float		transmittance;

	rgb_shades[DIFFUSE] = (t_vec4){{0.0f, 0.0f, 0.0f, 1.0f}};
	rgb_shades[SPECULAR] = (t_vec4){{0.0f, 0.0f, 0.0f, 1.0f}};
	i = 0;
	while (i < args->num_lights)
	{
		diffuse_specular(
			rec, &(args->light_wrappers[i]), rgb_shades);
		transmittance = get_transmittance(
			rec, &(args->light_wrappers[i]), args->object_wrappers, args->num_objects);
		rgb_shades[DIFFUSE] = scalar_mul_vec(transmittance, &(rgb_shades[DIFFUSE]));
		rgb_shades[SPECULAR] = scalar_mul_vec(transmittance, &(rgb_shades[SPECULAR]));
		i++;
	}
}

t_vec4				ray_color(
	t_trace_record *rec,
	int depth,
	t_global_rt_args *args
)
{
	t_vec4		rgb_shades[5];

	rgb_shades[AMBIENT] = ambient(args->i_a, &(rec->object_wrapper->k_a));
	diffuse_specular_per_light(rec, args, rgb_shades);
	rgb_shades[REFLECT] = reflection(rec, depth, args);
	rgb_shades[REFRACT] = refraction(rec, depth, args);
	return (cal_color(rec->object_wrapper, rgb_shades));
}