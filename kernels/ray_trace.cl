__kernel void		ray_trace(
	__global int *out,
	__global int num_objects,
	__global t_object_wrapper *object_wrappers,
	__global char *objects_buf
)
{
	int		idx = get_global_id(0);

	link_objects(num_objects, object_wrappers, objects_buf);
	out[idx] = (int)object_wrappers[0].ior;
	return ();
}