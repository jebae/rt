#include "rt.h"

int				trace(
	t_ray *ray,
	t_trace_record *prev_rec,
	t_trace_record *rec,
	t_global_rt_args *args
)
{
	int					i;
	float				t[2];

	t[1] = INFINITY;
	i = -1;
	while (++i < args->num_objects)
	{
		if ((&(args->object_wrappers[i]))->intersect(
			(&(args->object_wrappers[i]))->object, ray, &(t[0])) == RT_FALSE)
			continue ;
		if (t[0] > t[1])
			continue ;
		t[1] = t[0];
		rec->object_wrapper = &(args->object_wrappers[i]);
	}
	if (t[1] == INFINITY)
		return (RT_FALSE);
	rec->point = hit_point(ray, t[1]);
	rec->normal = rec->object_wrapper->get_normal(
		rec->object_wrapper->object, &(rec->point));
	if (vec_dot_vec(&(rec->normal), &(ray->d)) > 0.0f)
		rec->normal = scalar_mul_vec(-1.0f, &(rec->normal));
	rec->ray = ray;
	rec->prev = prev_rec;
	return (RT_TRUE);
}