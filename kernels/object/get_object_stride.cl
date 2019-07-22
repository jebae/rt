size_t		get_object_stride(__global char *objects_buf)
{
	int		type;

	type = *(__global int *)objects_buf;
	if (type == RT_OBJECT_TYPE_SPHERE)
		return (sizeof(t_sphere) + sizeof(int));
	else if (type == RT_OBJECT_TYPE_CONE)
		return (sizeof(t_cone) + sizeof(int));
	else if (type == RT_OBJECT_TYPE_PLANE)
		return (sizeof(t_plane) + sizeof(int));
	else if (type == RT_OBJECT_TYPE_TRIANGLE)
		return (sizeof(t_triangle) + sizeof(int));
	else if (type == RT_OBJECT_TYPE_CYLINDER)
		return (sizeof(t_cylinder) + sizeof(int));
	return (0);
}