int			intersect(
	__global char *objects_buf,
	t_ray *ray,
	float *t,
	size_t *stride
)
{
	int		res;
	int		type;

	res = RT_FALSE;
	type = *((int *)objects_buf);
	if (type == RT_OBJECT_TYPE_SPHERE)
		res = sphere_intersect(objects_buf + sizeof(int), ray, t);
	*stride = get_stride(type) + sizeof(int);
	return (res);
}