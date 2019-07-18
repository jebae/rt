#include "rt.h"

size_t		new_sphere(
	t_object_commons commons,
	t_new_sphere_args *args_sphere,
	char *objects_buf
)
{
	t_sphere			sphere;

	sphere.commons = commons;
	sphere.c = args_sphere->c;
	sphere.r = args_sphere->r;
	write_mem_buf(objects_buf, (char *)&sphere, sizeof(sphere), RT_OBJECT_TYPE_SPHERE);
	return (sizeof(sphere) + sizeof(int));
}