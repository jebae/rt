#include "rt.h"

static t_vec4			disk_normal(
	void *object,
	t_vec4 *point
)
{
	point = NULL;
	return (plane_normal((void *)(&((t_disk *)object)->plane), point));
}

static int				disk_intersect(
	void *object,
	t_ray *ray,
	float *t
)
{
	t_disk		*disk;
	t_vec4		v;

	disk = (t_disk *)object;
	if (plane_intersect((void *)&(disk->plane), ray, t) == RT_FALSE)
		return (RT_FALSE);
	v = hit_point(ray, *t);
	v = vec_sub_vec(&v, &(disk->plane.p));
	if (vec_dot_vec(&v, &v) > disk->r * disk->r)
		return (RT_FALSE);
	return (RT_TRUE);
}

t_object_wrapper		new_disk(
	t_new_object_args *args_obj,
	t_new_disk_args *args_disk
)
{
	t_object_wrapper	object_wrapper;
	t_disk				*disk;

	object_wrapper.object = ft_memalloc(sizeof(t_disk));
	if (object_wrapper.object == NULL)
		exit_with_memalloc_err("disk");
	set_new_object(&object_wrapper, args_obj,
		&disk_intersect, &disk_normal);
	disk = (t_disk *)object_wrapper.object;
	disk->r = args_disk->r;
	disk->plane.p = args_disk->p;
	disk->plane.n = normalize(&(args_disk->n));
	return (object_wrapper);
}