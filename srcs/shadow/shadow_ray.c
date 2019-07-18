// #include "rt.h"

// static t_ray		get_shadow_ray(
// 	t_trace_record *rec,
// 	t_light_wrapper *light_wrapper
// )
// {
// 	t_ray				shadow_ray;

// 	shadow_ray.e = scalar_mul_vec(RT_BIAS, &(rec->normal));
// 	shadow_ray.e = vec_plus_vec(&(rec->point), &(shadow_ray.e));
// 	shadow_ray.d = light_wrapper->get_light_direction(
// 		light_wrapper->light, &(shadow_ray.e));
// 	shadow_ray.d = scalar_mul_vec(-1.0f, &(shadow_ray.d));
// 	return (shadow_ray);
// }

// float				get_transmittance(
// 	t_trace_record *rec,
// 	t_light_wrapper *light_wrapper,
// 	t_object_wrapper *object_wrappers,
// 	int num_objects
// )
// {
// 	int					i;
// 	float				t;
// 	float				transmittance;
// 	t_ray				shadow_ray;

// 	transmittance = 1.0f;
// 	shadow_ray = get_shadow_ray(rec, light_wrapper);
// 	i = 0;
// 	while (i < num_objects)
// 	{
// 		if (object_wrappers[i].intersect(
// 			object_wrappers[i].object, &shadow_ray, &t))
// 			transmittance *= object_wrappers[i].transparency;
// 		i++;
// 	}
// 	return (transmittance);
// }