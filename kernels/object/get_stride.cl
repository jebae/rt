size_t		get_stride(int type)
{
	if (type == RT_OBJECT_TYPE_SPHERE)
		return (sizeof(t_sphere));
}