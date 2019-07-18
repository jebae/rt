#include "rt_test.h"
#include "rt_parallel.h"

static float		WIDTH = 100;
static float		HEIGHT = 80;

// static void						disp_buf(const int *buf)
// {
// 	for (int i=0; i < HEIGHT; i++)
// 	{
// 		for (int j=0; j < WIDTH; j++)
// 			printf("%d ", buf[i * (int)WIDTH + j]);
// 		printf("\n");
// 	}
// }

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

	commons.ior = 4.2f;
	args_sphere.r = 4.0f;
	args_sphere.c = (t_vec4){{0.0f, 5.0f, 0.0f, 1.0f}};
	return (new_sphere(commons, &args_sphere, objects_buf));
}

static void			write_objects(char *objects_buf)
{
	objects_buf += get_sphere(objects_buf);
}

void						test_sphere_intersect(void)
{
	t_test_dispatcher	dispatcher;
	size_t				buf_size;
	t_clkit				clkit;
	t_global_settings	settings;
	static char			*srcs[] = {
		"kernels/header.cl",
		"kernels/gmath/vec4/vec4_operator.cl",
		"kernels/preprocess/set_global_settings.cl",
		"kernels/object/get_normal.cl",
		"kernels/object/get_stride.cl",
		"kernels/object/intersect.cl",
		"kernels/object/sphere.cl",
		"kernels/ray/hit_point.cl",
		"kernels/ray/ray_origin.cl",
		"kernels/ray/trace.cl",
		"kernels/utils/swap.cl",
		"kernels/__tests__/intersect.test.cl"
	};

	init_mlx(&dispatcher, WIDTH, HEIGHT);
	init_marker(&(dispatcher.marker), dispatcher.p_mlx, dispatcher.p_win, &settings);

	settings.kernel_name = "intersect_test";
	settings.ray_grid_props = get_ray_grid_props_for_test();
	settings.window_width = WIDTH;
	settings.window_height = HEIGHT;
	settings.num_objects = 1;

	settings.img_buf = (int *)get_img_buffer(
		dispatcher.marker.p_img, settings.window_width);

	buf_size = sizeof(t_sphere) + sizeof(int) * settings.num_objects;
	settings.objects_buf_size = buf_size;
	settings.objects_buf = (char *)ft_memalloc(buf_size);

	write_objects(settings.objects_buf);

	if (init_clkit(
		&clkit, srcs, sizeof(srcs) / sizeof(char *), &settings) == RT_FAIL)
		return ;
	if (set_kernel_args(*(clkit.kernels), clkit.mems, &settings) == RT_FAIL)
		return ;
	enqueue_ndrange_kernel(*(clkit.cmd_queues), *(clkit.kernels),
		settings.window_width * settings.window_height);

	enqueue_read_buffer(*(clkit.cmd_queues),
		clkit.mems[RT_CL_MEM_IMAGE], settings.img_buf, &settings);

	// execute_cmd_queue(*clkit.cmd_queues);
	// release(&clkit);
	// printf("release\n");
	// // disp_buf(settings.img_buf);
	// printf(KGRN "done\n" KNRM);
	// clear_global_settings(&settings);
	// mlx_put_image_to_window(
	// 	dispatcher.marker.p_mlx,
	// 	dispatcher.marker.p_win,
	// 	dispatcher.marker.p_img, 0, 0);
	// mlx_loop(dispatcher.p_mlx);
}