t_vec4			get_normal(
	__global char *objects_buf,
	t_vec4 *point
)
{
	int			type;
	t_vec4		dumb_normal;

	type = *((int *)objects_buf);
	if (type == RT_OBJECT_TYPE_SPHERE)
		return (sphere_normal(objects_buf + sizeof(int), point));
	return (dumb_normal);
}