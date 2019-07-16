#include "rt.h"

t_vec4				plane_normal(
	void *object,
	t_vec4 *point
)
{
	point = NULL;
	return (((t_plane *)object)->n);
}

int					plane_intersect(
	void *object,
	t_ray *ray,
	float *t
)
{
	float		det;
	t_plane		*plane;
	t_vec4		v;

	plane = (t_plane *)object;
	det = vec_dot_vec(&(ray->d), &(plane->n));
	if (ABS(det) <= FLOAT_0)
		return (RT_FALSE);
	v = vec_sub_vec(&(plane->p), &(ray->e));
	*t = vec_dot_vec(&v, &(plane->n)) / det;
	if (*t < 0.0f)
		return (RT_FALSE);
	return (RT_TRUE);
}

t_object_wrapper	new_plane(
	t_new_object_args *args_obj,
	t_new_plane_args *args_plane
)
{
	t_object_wrapper	object_wrapper;
	t_plane				*plane;

	object_wrapper.object = ft_memalloc(sizeof(t_plane));
	if (object_wrapper.object == NULL)
		exit_with_memalloc_err("plane");
	set_new_object(&object_wrapper, args_obj,
		&plane_intersect, &plane_normal);
	plane = (t_plane *)object_wrapper.object;
	plane->p = args_plane->p;
	plane->n = normalize(&(args_plane->n));
	return (object_wrapper);
}