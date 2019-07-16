#include "rt_test.h"
#include "rt_parallel.h"

static float		WIDTH = 1000;
static float		HEIGHT = 600;

static t_object_wrapper		get_sphere(void)
{
	t_new_sphere_args			args_sphere;
	t_new_object_args			args_obj;

	args_obj.type = RT_OBJECT_TYPE_SPHERE;
	args_obj.reflectivity = 0.1f;
	args_obj.transparency = 0.9f;
	args_obj.ior = 1.5f;
	args_obj.k_a = (t_vec4){{0.9f, 0.6f, 0.1f, 1}};
	args_obj.k_d = (t_vec4){{0.9f, 0.6f, 0.1f, 1}};
	args_obj.k_s = (t_vec4){{0.5f, 0.5f, 0.5f, 1}};
	args_obj.specular_alpha = 50;
	args_sphere.r = 2;
	args_sphere.c = (t_vec4){{1.0f, 10.0f, 2.0f, 1}};
	return (new_sphere(&args_obj, &args_sphere));
}

static t_object_wrapper		get_cone(void)
{
	t_new_cone_args			args_cone;
	t_new_object_args			args_obj;

	args_obj.type = RT_OBJECT_TYPE_CONE;
	args_obj.specular_alpha = 50;
	args_obj.reflectivity = 0.7f;
	args_obj.transparency = 0.0f;
	args_obj.ior = 1.5f;
	args_obj.k_a = (t_vec4){{0.2f, 0.5f, 0.7f, 1}};
	args_obj.k_d = (t_vec4){{0.2f, 0.5f, 0.7f, 1}};
	args_obj.k_s = (t_vec4){{0.5f, 0.5f, 0.5f, 1}};
	args_cone.theta = M_PI / 6.0f;
	args_cone.h = 2.0f;
	args_cone.c = (t_vec4){{-2.0f, 6.0f, 0.0f, 1}};
	args_cone.v = (t_vec4){{1.0f, 0.0f, -1.0f, 1}};
	return (new_cone(&args_obj, &args_cone));
}

void						test_cl_link_objects(void)
{
	t_clkit				clkit;
	t_global_settings	args;
	t_object_wrapper	object_wrappers[2];
	char		*srcs[] = {
		"kernels/header.cl",
		"kernels/link_object.cl",
		"kernels/ray_trace.cl"
	};

	object_wrappers[0] = get_sphere();
	object_wrappers[1] = get_cone();
	args.window_width = WIDTH;
	args.window_height = WIDTH;
	args.object_wrappers = object_wrappers;
	args.num_objects = sizeof(object_wrappers) / sizeof(t_object_wrapper);
	init_clkit(&clkit, srcs, sizeof(srcs) / sizeof(char *), &args);
}