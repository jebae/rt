#include "rt.h"

t_ray				get_reflect_ray(t_trace_record *rec)
{
	float		n_ray;
	t_ray		reflect_ray;

	n_ray = -1.0f * vec_dot_vec(&(rec->normal), &(rec->ray->d));
	reflect_ray.d = scalar_mul_vec(2.0f * n_ray, &(rec->normal));
	reflect_ray.d = vec_plus_vec(&(rec->ray->d), &(reflect_ray.d));
	reflect_ray.e = scalar_mul_vec(RT_BIAS, &(rec->normal));
	reflect_ray.e = vec_plus_vec(&(rec->point), &(reflect_ray.e));
	reflect_ray.ior_medium = rec->ray->ior_medium;
	reflect_ray.type = RT_RAY_TYPE_REFLECTION;
	return (reflect_ray);
}

t_vec4				reflection(
	t_trace_record *rec_origin,
	int depth,
	t_global_rt_args *args
)
{
	t_vec4					rgb;
	t_vec4					rgb_reflected;
	t_trace_record			rec;
	t_ray					reflect_ray;

	rgb = (t_vec4){{0.0f, 0.0f, 0.0f, 1.0f}};
	if (depth >= RT_DEPTH_LIMIT)
		return (rgb);
	reflect_ray = get_reflect_ray(rec_origin);
	if (!trace(&reflect_ray, rec_origin, &rec, args))
		return (rgb);
	rgb_reflected = ray_color(&rec, depth + 1, args);
	return (vec_plus_vec(&rgb_reflected, &rgb));
}