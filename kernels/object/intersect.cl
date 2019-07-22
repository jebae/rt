int			intersect(
	__global char *objects_buf,
	t_ray *ray,
	float *t
)
{
	int		res;
	int		type;

	res = RT_FALSE;
	type = *((__global int *)objects_buf);
	if (type == RT_OBJECT_TYPE_SPHERE)
		res = sphere_intersect(objects_buf + sizeof(int), ray, t);
	else if (type == RT_OBJECT_TYPE_CONE)
		res = cone_intersect(objects_buf + sizeof(int), ray, t);
	else if (type == RT_OBJECT_TYPE_PLANE)
		res = plane_intersect(objects_buf + sizeof(int), ray, t);
	else if (type == RT_OBJECT_TYPE_TRIANGLE)
		res = triangle_intersect(objects_buf + sizeof(int), ray, t);
	else if (type == RT_OBJECT_TYPE_CYLINDER)
		res = cylinder_intersect(objects_buf + sizeof(int), ray, t);
	return (res);
}