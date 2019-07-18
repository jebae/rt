#include "rt.h"

size_t		new_plane(
	t_object_commons commons,
	t_new_plane_args *args_plane,
	char *objects_buf
)
{
	t_plane				plane;

	plane.commons = commons;
	plane.p = args_plane->p;
	plane.n = normalize(&(args_plane->n));
	write_mem_buf(objects_buf, (char *)&plane, sizeof(plane), RT_OBJECT_TYPE_PLANE);
	return (sizeof(plane) + sizeof(int));
}