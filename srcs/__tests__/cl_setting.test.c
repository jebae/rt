#include "rt_test.h"
#include "rt_parallel.h"

static float		WIDTH = 1000;
static float		HEIGHT = 800;

static t_ray_grid_properties	get_ray_grid_props_for_test(void)
{
	t_ray_grid_properties	props;
	t_camera				cam;

	cam.focus = (t_vec4){{0, 1, 0, 1}};
	cam.pos = (t_vec4){{0, 0, 0, 1}};
	cam.roll = 0;
	props = get_ray_grid_properties(&cam, WIDTH, HEIGHT, M_PI / 2.0f);
	return (props);
}

static size_t		get_sphere(char *objects_buf)
{
	t_new_sphere_args			args_sphere;
	t_object_commons			commons;

	commons.reflectivity = 0.1f;
	commons.transparency = 0.9f;
	commons.ior = 4.5f;
	commons.color = (t_vec4){{0.9f, 0.6f, 0.1f, 1}};
	commons.specular_alpha = 50;
	args_sphere.r = 9.2f;
	args_sphere.c = (t_vec4){{1.0f, 10.0f, 2.0f, 1}};
	return (new_sphere(commons, &args_sphere, objects_buf));
}

static size_t		get_cone(char *objects_buf)
{
	t_new_cone_args			args_cone;
	t_object_commons		commons;

	commons.specular_alpha = 50;
	commons.reflectivity = 0.7f;
	commons.transparency = 0.0f;
	commons.ior = 8.0f;
	commons.color = (t_vec4){{0.2f, 0.5f, 0.7f, 1}};
	args_cone.theta = M_PI / 6.0f;
	args_cone.h = 3.0f;
	args_cone.c = (t_vec4){{-2.0f, 6.0f, 0.0f, 1}};
	args_cone.v = (t_vec4){{1.0f, 0.0f, -1.0f, 1}};
	return (new_cone(commons, &args_cone, objects_buf));
}

static void			write_objects(char *objects_buf)
{
	objects_buf += get_sphere(objects_buf);
	objects_buf += get_cone(objects_buf);
}

void						test_cl_setting(void)
{
	t_test_dispatcher	dispatcher;
	size_t				buf_size;
	t_clkit				clkit;
	t_global_settings	settings;
	static char			*srcs[] = {
		"kernels/header.cl",
		"kernels/gmath/vec4/vec4_operator.cl",
		"kernels/ray/ray_origin.cl",
		"kernels/main.cl"
	};

	init_mlx(&dispatcher, WIDTH, HEIGHT);
	init_marker(&(dispatcher.marker), dispatcher.p_mlx, dispatcher.p_win, &settings);

	settings.ray_grid_props = get_ray_grid_props_for_test();
	settings.window_width = WIDTH;
	settings.window_height = HEIGHT;
	settings.num_objects = 2;

	buf_size = sizeof(int) * (int)settings.window_width * (int)settings.window_height;
	settings.img_buf = (int *)ft_memalloc(buf_size);

	buf_size = sizeof(t_sphere) + sizeof(t_cone) + sizeof(int) * settings.num_objects;
	settings.objects_buf_size = buf_size;
	settings.objects_buf = (char *)ft_memalloc(buf_size);

	write_objects(settings.objects_buf);

	if (init_clkit(
		&clkit, srcs, sizeof(srcs) / sizeof(char *), &settings) == RT_FAIL)
		return ;
	if (set_kernel_args(*clkit.kernels, clkit.mems, &settings) == RT_FAIL)
		return ;
	enqueue_ndrange_kernel(*clkit.cmd_queues, *clkit.kernels,
		settings.window_width * settings.window_height);
	enqueue_read_buffer(*clkit.cmd_queues,
		clkit.mems[RT_CL_MEM_IMAGE], settings.img_buf, &settings);
	execute_cmd_queue(*clkit.cmd_queues);
	release(&clkit);
	clear_global_settings(&settings);
	mlx_put_image_to_window(
		dispatcher.marker.p_mlx,
		dispatcher.marker.p_win,
		dispatcher.marker.p_img, 0, 0);
	mlx_loop(dispatcher.p_mlx);
}