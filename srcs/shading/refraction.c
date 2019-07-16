#include "rt.h"

static float	get_ior(t_trace_record *rec)
{
	int					refract_count;
	t_ray				*recent_refraction_ray;
	t_trace_record		*cur;
	t_trace_record		*prev;

	refract_count = 0;
	recent_refraction_ray = NULL;
	cur = rec;
	prev = rec->prev;
	while (prev != NULL)
	{
		if (cur->ray->type == RT_RAY_TYPE_REFRACTION &&
			prev->object_wrapper == rec->object_wrapper)
		{
			if (recent_refraction_ray == NULL)
				recent_refraction_ray = cur->ray;
			refract_count++;
		}
		cur = prev;
		prev = prev->prev;
	}
	return (refract_count % 2 == 0 ?
		rec->object_wrapper->ior : recent_refraction_ray->ior_medium);
}

static t_ray	get_refract_ray(t_trace_record *rec)
{
	float			snell_ratio;
	float			d_n;
	float			det;
	t_vec4			v;
	t_ray			refract_ray;

	refract_ray.ior_medium = get_ior(rec);
	snell_ratio = rec->ray->ior_medium / refract_ray.ior_medium;
	d_n = -1.0f * vec_dot_vec(&(rec->ray->d), &(rec->normal));
	det = 1 - snell_ratio * snell_ratio * (1 - d_n * d_n);
	if (det < 0.0f)
	{
		refract_ray.type = RT_RAY_TYPE_NONE;
		return (refract_ray);
	}
	v = scalar_mul_vec(snell_ratio, &(rec->ray->d));
	refract_ray.d = scalar_mul_vec(snell_ratio * d_n - sqrtf(det), &(rec->normal));
	refract_ray.d = vec_plus_vec(&v, &(refract_ray.d));
	refract_ray.e = scalar_mul_vec(-1.0f * RT_BIAS, &(rec->normal));
	refract_ray.e = vec_plus_vec(&(rec->point), &(refract_ray.e));
	refract_ray.type = RT_RAY_TYPE_REFRACTION;
	return (refract_ray);
}

t_vec4			refraction(
	t_trace_record *rec_origin,
	int refract_count,
	t_global_rt_args *args
)
{
	t_vec4					rgb;
	t_vec4					rgb_refracted;
	t_trace_record			rec;
	t_ray					refract_ray;

	rgb = (t_vec4){{0.0f, 0.0f, 0.0f, 1.0f}};
	if (refract_count >= RT_DEPTH_LIMIT)
		return (rgb);
	refract_ray = get_refract_ray(rec_origin);
	if (refract_ray.type == RT_RAY_TYPE_NONE)
		return (rgb);
	if (!trace(&refract_ray, rec_origin, &rec, args))
		return (rgb);
	rgb_refracted = ray_color(&rec, refract_count + 1, args);
	return (vec_plus_vec(&rgb_refracted, &rgb));
}