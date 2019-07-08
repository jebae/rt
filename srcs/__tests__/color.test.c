#include "rt_test.h"

static float		WIDTH = 1000;
static float		HEIGHT = 600;
static t_vec4		i_a = (t_vec4){{0.1f, 0.1f, 0.1f}};

static t_ray_grid_properties	get_ray_grid_props_for_test(void)
{
	t_ray_grid_properties	props;
	t_camera				cam;

	cam.focus = (t_vec4){{0, 0, 10, 1}};
	cam.pos = (t_vec4){{10, 10, 10, 1}};
	cam.roll = 0;
	props = get_ray_grid_properties(&cam, WIDTH, HEIGHT, M_PI / 2.0f);
	return (props);
}

static t_object_wrapper			get_sphere(void)
{
	t_new_sphere_args			args_sphere;
	t_new_object_args			args_obj;

	args_obj.k_a = (t_vec4){{0.9f, 0.6f, 0.1f, 1}};
	args_obj.k_d = (t_vec4){{0.9f, 0.6f, 0.1f, 1}};
	args_obj.k_s = (t_vec4){{0.5f, 0.5f, 0.5f, 1}};
	args_obj.shine = 50;
	args_sphere.r = 2;
	args_sphere.c = (t_vec4){{3, 3, 3, 1}};
	return (new_sphere(&args_obj, &args_sphere));
}

static t_object_wrapper			get_triangle(void)
{
	t_new_triangle_args			args_triangle;
	t_new_object_args			args_obj;

	args_obj.k_a = (t_vec4){{0.1f, 0.6f, 0.9f, 1}};
	args_obj.k_d = (t_vec4){{0.1f, 0.6f, 0.9f, 1}};
	args_obj.k_s = (t_vec4){{0.5f, 0.5f, 0.5f, 1}};
	args_obj.shine = 5;
	args_triangle.a = (t_vec4){{3, 5, 3, 1}};
	args_triangle.u = (t_vec4){{-3, -1, 2}};
	args_triangle.v = (t_vec4){{0, -5, -2}};
	return (new_triangle(&args_obj, &args_triangle));
}

static t_object_wrapper			get_plane(void)
{
	t_new_plane_args			args_plane;
	t_new_object_args			args_obj;

	args_obj.k_a = (t_vec4){{0.1f, 0.9f, 0.6f, 1}};
	args_obj.k_d = (t_vec4){{0.1f, 0.9f, 0.6f, 1}};
	args_obj.k_s = (t_vec4){{0.5f, 0.5f, 0.5f, 1}};
	args_obj.shine = 5;
	args_plane.n = (t_vec4){{-1, -1, 1, 1}};
	args_plane.p = (t_vec4){{10, 10, -1, 1}};
	return (new_plane(&args_obj, &args_plane));
}

static t_object_wrapper			get_disk(void)
{
	t_new_disk_args				args_disk;
	t_new_object_args			args_obj;

	args_obj.k_a = (t_vec4){{0.4f, 0.7f, 0.2f, 1}};
	args_obj.k_d = (t_vec4){{0.4f, 0.7f, 0.2f, 1}};
	args_obj.k_s = (t_vec4){{0.5f, 0.5f, 0.5f, 1}};
	args_obj.shine = 25;
	args_disk.n = (t_vec4){{1.0f, 2.0f, 3.0f, 1}};
	args_disk.p = (t_vec4){{2.0f, -3.0f, 2.0f, 1}};
	args_disk.r = 2.0f;
	return (new_disk(&args_obj, &args_disk));
}

static t_object_wrapper			get_cone(void)
{
	t_new_cone_args				args_cone;
	t_new_object_args			args_obj;

	args_obj.k_a = (t_vec4){{0.2f, 0.5f, 0.7f, 1}};
	args_obj.k_d = (t_vec4){{0.2f, 0.5f, 0.7f, 1}};
	args_obj.k_s = (t_vec4){{0.5f, 0.5f, 0.5f, 1}};
	args_obj.shine = 25;
	args_cone.theta = M_PI / 6.0f;
	args_cone.h = 5.0f;
	args_cone.c = (t_vec4){{0.0f, 0.0f, 10.0f, 1}};
	args_cone.v = (t_vec4){{1.0f, 1.0f, -5.0f, 1}};
	return (new_cone(&args_obj, &args_cone));
}

static t_light_wrapper			get_light(void)
{
	t_light_wrapper				light_wrapper;
	t_new_light_args			args_light;
	t_new_distant_light_args	args_distant;

	args_light.i_d = (t_vec4){{1.0f, 1.0f, 1.0f}};
	args_light.i_s = (t_vec4){{1.0f, 1.0f, 1.0f}};
	args_distant.d = (t_vec4){{-1.0f, 0.0f, 0.0f, 1}};
	light_wrapper = new_distant_light(&args_light, &args_distant);
	return (light_wrapper);
}

static void						render_color(
	t_ray_grid_properties *props,
	t_object_wrapper *object_wrappers,
	t_light_wrapper *light_wrapper,
	int				num_objects
)
{
	float						t;
	t_ray						ray;
	t_vec4						color_shades[2];
	t_vec4						intersect;
	t_coord						p;
	t_object_wrapper			*object_wrapper;
	t_test_dispatcher			dispatcher;
	t_diffuse_specular_args		shading_args;

	init_mlx(&dispatcher, WIDTH, HEIGHT);
	init_marker(&(dispatcher.marker), dispatcher.p_mlx, dispatcher.p_win);
	for (int i=0; i < HEIGHT; i++)
	{
		for (int j=0; j < WIDTH; j++)
		{
			set_ray(props, &ray, j, i);
			for (int k=0; k < num_objects; k++)
			{
				object_wrapper = &(object_wrappers[k]);
				if (object_wrapper->intersect(object_wrapper->object, &ray, &t) == RT_FALSE)
					continue ;
				intersect = intersection_point(&ray, t);
				color_shades[0] = ambient(&i_a, &(object_wrapper->k_a));
				shading_args.light_wrapper = light_wrapper;
				shading_args.object_wrapper = object_wrapper;
				shading_args.point = &intersect;
				shading_args.ray_d = &(ray.d);
				color_shades[1] = diffuse_specular(&shading_args);
				dispatcher.marker.color = cal_color(
					vec_plus_vec(&(color_shades[0]), &(color_shades[1]))
				);
				p.x = j;
				p.y = i;
				dispatcher.marker.mark_pixel(&(dispatcher.marker), &p, NULL);
			}
		}
	}
	for (int k=0; k < num_objects; k++)
		ft_memdel((void **)&(object_wrappers[k].object));
	ft_memdel((void **)&(light_wrapper->light));
	mlx_loop(dispatcher.p_mlx);
}

void							test_color(void)
{
	t_ray_grid_properties		props;
	t_object_wrapper			object_wrappers[1];
	t_light_wrapper				light_wrapper;
	
	props = get_ray_grid_props_for_test();
	object_wrappers[0] = get_plane();
	object_wrappers[0] = get_triangle();
	object_wrappers[0] = get_sphere();
	object_wrappers[0] = get_disk();
	object_wrappers[0] = get_cone();
	light_wrapper = get_light();
	render_color(&props, object_wrappers, &light_wrapper,\
		sizeof(object_wrappers) / sizeof(t_object_wrapper));
}