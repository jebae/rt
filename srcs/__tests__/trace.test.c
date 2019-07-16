#include "rt.h"

#include "rt_test.h"

static float		WIDTH = 1000;
static float		HEIGHT = 800;
static t_vec4		i_a = (t_vec4){{0.2f, 0.2f, 0.2f}};

static t_ray_grid_properties	get_ray_grid_props_for_test(void)
{
	t_ray_grid_properties	props;
	t_camera				cam;

	cam.focus = (t_vec4){{0.0f, 1.0f, 0.0f, 1}};
	cam.pos = (t_vec4){{0.0f, 0.0f, 0.0f, 1}};
	cam.roll = 0;
	props = get_ray_grid_properties(&cam, WIDTH, HEIGHT, M_PI / 2.0f);
	return (props);
}

static void						delete_all(
	t_object_wrapper *object_wrappers,
	t_light_wrapper *light_wrappers,
	int num_objects,
	int num_lights
)
{
	int		i;

	for (i=0; i < num_objects; i++)
		ft_memdel((void **)&(object_wrappers[i].object));
	for (i=0; i < num_lights; i++)
		ft_memdel((void **)&(light_wrappers[i].light));
}

static t_object_wrapper		get_sphere(void)
{
	t_new_sphere_args			args_sphere;
	t_new_object_args			args_obj;

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

static t_object_wrapper		get_inner_sphere(void)
{
	t_new_sphere_args			args_sphere;
	t_new_object_args			args_obj;

	args_obj.reflectivity = 0.0f;
	args_obj.transparency = 1.0f;
	args_obj.ior = 1.0f;
	args_obj.k_a = (t_vec4){{0.9f, 0.6f, 0.1f, 1}};
	args_obj.k_d = (t_vec4){{0.9f, 0.6f, 0.1f, 1}};
	args_obj.k_s = (t_vec4){{0.5f, 0.5f, 0.5f, 1}};
	args_obj.specular_alpha = 50;
	args_sphere.r = 1.89;
	args_sphere.c = (t_vec4){{1.0f, 10.0f, 2.0f, 1}};
	return (new_sphere(&args_obj, &args_sphere));
}

t_object_wrapper				get_cone(void)
{
	t_new_cone_args				args_cone;
	t_new_object_args			args_obj;

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

t_object_wrapper				get_cylinder(void)
{
	t_new_cylinder_args			args_cylinder;
	t_new_object_args			args_obj;

	args_obj.reflectivity = 0.1f;
	args_obj.transparency = 0.7f;
	args_obj.ior = 1.5f;
	args_obj.k_a = (t_vec4){{0.7f, 0.2f, 0.3f, 1}};
	args_obj.k_d = (t_vec4){{0.7f, 0.2f, 0.3f, 1}};
	args_obj.k_s = (t_vec4){{0.5f, 0.5f, 0.5f, 1}};
	args_obj.specular_alpha = 50;
	args_cylinder.r = 1.0f;
	args_cylinder.h = 2.0f;
	args_cylinder.c = (t_vec4){{4.0f, 8.0f, 2.0f, 1}};
	args_cylinder.v = (t_vec4){{1.0f, -3.0f, 1.0f, 1}};
	return (new_cylinder(&args_obj, &args_cylinder));
}

t_object_wrapper				get_triangle(void)
{
	t_new_triangle_args			args_triangle;
	t_new_object_args			args_obj;

	args_obj.reflectivity = 0.1f;
	args_obj.transparency = 0.0f;
	args_obj.k_a = (t_vec4){{0.1f, 0.6f, 0.9f, 1}};
	args_obj.k_d = (t_vec4){{0.1f, 0.6f, 0.9f, 1}};
	args_obj.k_s = (t_vec4){{0.5f, 0.5f, 0.5f, 1}};
	args_obj.specular_alpha = 5;
	args_triangle.a = (t_vec4){{3, 5, 3, 1}};
	args_triangle.u = (t_vec4){{-3, -1, 2}};
	args_triangle.v = (t_vec4){{0, -5, -2}};
	return (new_triangle(&args_obj, &args_triangle));
}

t_object_wrapper				get_plane(void)
{
	t_new_plane_args			args_plane;
	t_new_object_args			args_obj;

	args_obj.reflectivity = 0.1f;
	args_obj.transparency = 0.0f;
	args_obj.ior = 1.5;
	args_obj.k_a = (t_vec4){{0.1f, 0.9f, 0.6f, 1}};
	args_obj.k_d = (t_vec4){{0.1f, 0.9f, 0.6f, 1}};
	args_obj.k_s = (t_vec4){{0.5f, 0.5f, 0.5f, 1}};
	args_obj.specular_alpha = 5;
	args_plane.n = (t_vec4){{0.0f, 0.0f, 1.0f, 1}};
	args_plane.p = (t_vec4){{0.0f, 0.0f, -1.0f, 1}};
	return (new_plane(&args_obj, &args_plane));
}

t_object_wrapper				get_disk(void)
{
	t_new_disk_args				args_disk;
	t_new_object_args			args_obj;

	args_obj.reflectivity = 0.1f;
	args_obj.transparency = 0.0f;
	args_obj.k_a = (t_vec4){{0.4f, 0.7f, 0.2f, 1}};
	args_obj.k_d = (t_vec4){{0.4f, 0.7f, 0.2f, 1}};
	args_obj.k_s = (t_vec4){{0.5f, 0.5f, 0.5f, 1}};
	args_obj.specular_alpha = 25;
	args_disk.n = (t_vec4){{1.0f, 2.0f, 3.0f, 1}};
	args_disk.p = (t_vec4){{2.0f, -3.0f, 2.0f, 1}};
	args_disk.r = 2.0f;
	return (new_disk(&args_obj, &args_disk));
}

static t_light_wrapper			get_light(void)
{
	t_light_wrapper				light_wrapper;
	t_new_light_args			args_light;
	t_new_distant_light_args	args_distant;

	args_light.i_d = (t_vec4){{1.0f, 1.0f, 1.0f}};
	args_light.i_s = (t_vec4){{1.0f, 1.0f, 1.0f}};
	args_distant.d = (t_vec4){{1.0f, 1.0f, -1.0f, 1}};
	light_wrapper = new_distant_light(&args_light, &args_distant);
	return (light_wrapper);
}

static void						render_trace(
	t_ray_grid_properties *props,
	t_object_wrapper *object_wrappers,
	t_light_wrapper *light_wrappers,
	int num_objects,
	int num_lights
)
{
	t_coord						p;
	t_ray						ray;
	t_test_dispatcher			dispatcher;
	t_global_settings			args;
	t_trace_record				rec;

	init_mlx(&dispatcher, WIDTH, HEIGHT);
	init_marker(&(dispatcher.marker), dispatcher.p_mlx, dispatcher.p_win);
	args.num_objects = num_objects;
	args.num_lights = num_lights;
	args.object_wrappers = object_wrappers;
	args.light_wrappers = light_wrappers;
	args.i_a = &i_a;
	for (int i=0; i < HEIGHT; i++)
	{
		for (int j=0; j < WIDTH; j++)
		{
			set_ray(props, &ray, j, i);
			if (trace(&ray, NULL, &rec, &args))
			{
				dispatcher.marker.color = rgb_to_int(ray_color(&rec, 0, &args));
				p.x = j;
				p.y = i;
				dispatcher.marker.mark_pixel(&(dispatcher.marker), &p, NULL);
			}
		}
	}
	delete_all(object_wrappers, light_wrappers, num_objects, num_lights);
	mlx_loop(dispatcher.p_mlx);
}

void							test_trace(void)
{
	t_ray_grid_properties		props;
	t_object_wrapper			object_wrappers[5];
	t_light_wrapper				light_wrapper;
	
	props = get_ray_grid_props_for_test();
	object_wrappers[0] = get_sphere();
	object_wrappers[1] = get_inner_sphere();
	object_wrappers[2] = get_cone();
	object_wrappers[3] = get_cylinder();
	object_wrappers[4] = get_plane();
	// object_wrappers[1] = get_triangle();
	// object_wrappers[3] = get_disk();
	light_wrapper = get_light();
	render_trace(&props, object_wrappers, &light_wrapper,\
		sizeof(object_wrappers) / sizeof(t_object_wrapper),
		1);
}