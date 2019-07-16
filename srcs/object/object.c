#include "rt.h"

void		set_new_object(
	t_object_wrapper *object_wrapper,
	t_new_object_args *args,
	int (*intersect)(void *, t_ray *, float *),
	t_vec4 (*get_normal)(void *, t_vec4 *)
)
{
	object_wrapper->type = args->type;
	object_wrapper->reflectivity = args->reflectivity;
	object_wrapper->transparency = args->transparency;
	object_wrapper->ior = args->ior;
	object_wrapper->k_a = args->k_a;
	object_wrapper->k_d = args->k_d;
	object_wrapper->k_s = args->k_s;
	object_wrapper->specular_alpha = args->specular_alpha;
}