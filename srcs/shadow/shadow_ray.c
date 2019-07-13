#include "rt.h"

int			shadow_ray_hit(
	t_trace_record *rec,
	t_light_wrapper *light_wrapper,
	t_global_rt_args *args
)
{
	t_ray				shadow_ray;
	t_trace_record		dumb_rec;

	shadow_ray.e = scalar_mul_vec(RT_BIAS, &(rec->normal));
	shadow_ray.e = vec_plus_vec(&(rec->point), &(shadow_ray.e));
	shadow_ray.d = light_wrapper->get_light_direction(
		light_wrapper->light, &(shadow_ray.e));
	shadow_ray.d = scalar_mul_vec(-1.0f, &(shadow_ray.d));
	return (trace(&shadow_ray, NULL, &dumb_rec, args));
}