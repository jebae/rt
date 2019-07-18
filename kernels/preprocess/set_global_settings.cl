void	set_global_settings(
	t_global_settings *settings,
	__global char *objects_buf,
	int num_objects
)
{
	settings->num_objects = num_objects;
	settings->objects_buf = objects_buf;
}