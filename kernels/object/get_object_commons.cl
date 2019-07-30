t_object_commons	get_object_commons(__global char *buf)
{
	return (*(__global t_object_commons *)(buf + sizeof(int)));
}

float				get_transparency(__global char *objects_buf)
{
	t_object_commons	commons;

	commons = get_object_commons(objects_buf);
	return (commons.transparency);
}

float				get_object_ior(__global char *objects_buf)
{
	t_object_commons	commons;

	commons = get_object_commons(objects_buf);
	return (commons.ior);
}
