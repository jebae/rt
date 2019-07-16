size_t		get_stride(char type)
{
	switch (type)
	{
		case RT_OBJECT_TYPE_SPHERE:
			return (sizeof(t_sphere));
		case RT_OBJECT_TYPE_CONE:
			return (sizeof(t_cone));
		default :
			return (0);
	}
}

void		link_objects(
	__global int num_objects,
	__global t_object_wrapper *object_wrappers,
	__global char *objects_buf
)
{
	int		i;

	i = 0;
	while (i < num_objects)
	{
		object_wrappers[i].object = objects_buf;
		objects_buf += get_stride(object_wrappers[i].type);
		object_wrappers[i].ior = 4.2f;
		i++;
	}
}