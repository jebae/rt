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
	while (i < 4)
	{
		res = vec_plus_vec(&(rgb_shades[i]), &res);
		i++;
	}
	return (res);
}

static t_vec4		diffuse_specular_per_light(
	t_trace_record *rec,
	t_vec4 *ray_d,
	t_global_rt_args *args
)
{
	int			i;
	t_vec4		rgb_shade;
	t_vec4		temp_rgb_shade;

	rgb_shade = (t_vec4){{0.0f, 0.0f, 0.0f, 1.0f}};
	i = -1;
	while (++i < args->num_lights)
	{
		// if (shadow_ray_hit(rec, &(args->light_wrappers[i]), args))
		// 	continue ;
		temp_rgb_shade = diffuse_specular(
			ray_d, rec, &(args->light_wrappers[i]));
		rgb_shade = vec_plus_vec(&rgb_shade, &temp_rgb_shade);
	}
	return (rgb_shade);
}

t_vec4				ray_color(
	t_trace_record *rec,
	int depth,
	t_global_rt_args *args
)
{
	t_vec4		rgb_shades[4];

	rgb_shades[AMBIENT] = ambient(args->i_a, &(rec->object_wrapper->k_a));
	rgb_shades[DIFFUSE] = diffuse_specular_per_light(rec, &(rec->ray->d), args);
	rgb_shades[REFLECT] = reflection(rec, depth, args);
	rgb_shades[REFRACT] = refraction(rec, depth, args);
	return (cal_color(rec->object_wrapper, rgb_shades));
}