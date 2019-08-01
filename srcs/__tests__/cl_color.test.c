#include "rt_test.h"
#include "rt.h"

static float		WIDTH = 1600;
static float		HEIGHT = 1200;
static t_vec4		i_a = (t_vec4){{0.05f, 0.05f, 0.05f, 1.0f}};

static t_ray_grid_properties	get_ray_grid_props_for_test(void)
{
	t_ray_grid_properties	props;
	t_camera				cam;
	t_vec4					focus;

	focus = (t_vec4){{0, 3.0, 0, 1}};
	cam.pos = (t_vec4){{0, 0.0, 0.0f, 1}};
	cam.roll = 0;
	set_camera_axis(&cam, &focus);
	props = get_ray_grid_properties(&cam, WIDTH, HEIGHT, M_PI / 2.0f);
	return (props);
}

static size_t		get_sphere(char *objects_buf)
{
	t_new_sphere_args			args_sphere;
	t_object_commons			commons;

	commons.specular_alpha = 50;
	commons.reflectivity = 0.1f;
	commons.transparency = 0.0f;
	commons.ior = 1.5f;
	commons.color = (t_vec4){{0.9f, 0.6f, 0.1f, 1}};
	args_sphere.r = 1.0f;
	args_sphere.c = (t_vec4){{-2.0f, 5.0f, 0.5f, 1.0f}};
	return (new_sphere(commons, &args_sphere, objects_buf));
}

static size_t		get_cone(char *objects_buf)
{
	t_new_cone_args				args_cone;
	t_object_commons			commons;

	commons.specular_alpha = 50;
	commons.reflectivity = 0.3f;
	commons.transparency = 0.0f;
	commons.ior = 1.5f;
	commons.color = (t_vec4){{0.8f, 0.2f, 0.7f, 1}};
	args_cone.theta = M_PI / 6.0f;
	args_cone.h = 1.0f;
	args_cone.c = (t_vec4){{1.5f, 4.0f, 1.0f, 1.0f}};
	args_cone.v = (t_vec4){{-0.5f, -1.0f, -3.0f, 1.0f}};
	return (new_cone(commons, &args_cone, objects_buf));
}

static size_t		get_cylinder(char *objects_buf)
{
	t_new_cylinder_args			args_cylinder;
	t_object_commons			commons;

	commons.specular_alpha = 50;
	commons.reflectivity = 0.8f;
	commons.transparency = 0.0f;
	commons.ior = 1.5f;
	commons.color = (t_vec4){{0.1f, 0.6f, 0.3f, 1}};
	args_cylinder.r = 1.0f;
	args_cylinder.h = 1.5f;
	args_cylinder.c = (t_vec4){{0.0f, 5.0f, 2.0f, 1.0f}};
	args_cylinder.v = (t_vec4){{0.5f, -0.5f, -1.5f, 1.0f}};
	return (new_cylinder(commons, &args_cylinder, objects_buf));
}

static size_t		get_cylinder2(char *objects_buf)
{
	t_new_cylinder_args			args_cylinder;
	t_object_commons			commons;

	commons.specular_alpha = 50;
	commons.reflectivity = 0.0f;
	commons.transparency = 0.0f;
	commons.ior = 1.5f;
	commons.color = (t_vec4){{0.1f, 0.6f, 0.3f, 1}};
	args_cylinder.r = 0.99f;
	args_cylinder.h = 1.5f;
	args_cylinder.c = (t_vec4){{0.0f, 5.0f, 2.0f, 1.0f}};
	args_cylinder.v = (t_vec4){{0.5f, -0.5f, -1.5f, 1.0f}};
	return (new_cylinder(commons, &args_cylinder, objects_buf));
}

static size_t		get_plane(char *objects_buf)
{
	t_new_plane_args			args_plane;
	t_object_commons			commons;

	commons.reflectivity = 0.0f;
	commons.transparency = 0.0f;
	commons.ior = 1.5;
	commons.color = (t_vec4){{1.0f, 1.0f, 1.0f, 1}};
	commons.specular_alpha = 50;
	args_plane.n = (t_vec4){{0.0f, 0.0f, 1.0f, 1}};
	args_plane.p = (t_vec4){{0.0f, 0.0f, -1.0f, 1}};
	return (new_plane(commons, &args_plane, objects_buf));
}

static size_t		get_distant_light(char *lights_buf)
{
	t_new_distant_light_args	args_light;
	t_light_commons				commons;

	commons.intensity = (t_vec4){{1.0f, 1.0f, 1.0f}};
	args_light.d = (t_vec4){{1.0f, 1.0f, -1.0f, 1}};
	return (new_distant_light(commons, &args_light, lights_buf));
}

static size_t		get_spherical_light(char *lights_buf)
{
	t_new_spherical_light_args		args_light;
	t_light_commons					commons;

	commons.intensity = (t_vec4){{20.0f, 20.0f, 20.0f}};
	args_light.origin = (t_vec4){{0.0f, 3.0f, 1.0f, 1}};
	return (new_spherical_light(commons, &args_light, lights_buf));
}

static size_t		get_spherical_light2(char *lights_buf)
{
	t_new_spherical_light_args		args_light;
	t_light_commons					commons;

	commons.intensity = (t_vec4){{20.0f, 20.0f, 20.0f}};
	args_light.origin = (t_vec4){{-3.0f, 3.0f, 1.0f, 1}};
	return (new_spherical_light(commons, &args_light, lights_buf));
}

static void			write_objects(char *objects_buf)
{
	objects_buf += get_sphere(objects_buf);
	objects_buf += get_cone(objects_buf);
	objects_buf += get_cylinder(objects_buf);
	objects_buf += get_cylinder2(objects_buf);
	objects_buf += get_plane(objects_buf);
	// objects_buf += get_triangle(objects_buf);
}

static void			write_lights(char *lights_buf)
{
	lights_buf += get_distant_light(lights_buf);
	lights_buf += get_spherical_light(lights_buf);
	lights_buf += get_spherical_light2(lights_buf);
}

void						test_cl_color(int parallel_mode)
{
	t_test_dispatcher		dispatcher;
	size_t					buf_size;
	t_clkit					clkit;
	t_global_settings		settings;

	settings.parallel_mode = parallel_mode;
	settings.window_width = WIDTH;
	settings.window_height = HEIGHT;
	init_mlx(&dispatcher, WIDTH, HEIGHT);
	init_marker(&(dispatcher.marker), dispatcher.p_mlx, dispatcher.p_win, &settings);

	settings.ray_grid_props = get_ray_grid_props_for_test();
	settings.i_a = i_a;

	settings.img_buf = (int *)get_img_buffer(
		dispatcher.marker.p_img, settings.window_width);

	settings.num_objects = 5;
	buf_size = sizeof(t_sphere) + sizeof(t_cone) + sizeof(t_plane) +
		sizeof(t_cylinder) + sizeof(t_cylinder) +
		sizeof(int) * settings.num_objects;
	settings.objects_buf_size = buf_size;
	settings.objects_buf = (char *)ft_memalloc(buf_size);
	write_objects(settings.objects_buf);

	settings.num_lights = 3;
	buf_size = sizeof(t_spherical_light) + sizeof(t_spherical_light) +
		sizeof(t_distant_light) +
		sizeof(int) * settings.num_lights;
	settings.lights_buf_size = buf_size;
	settings.lights_buf = (char *)ft_memalloc(buf_size);
	write_lights(settings.lights_buf);

	if (init_clkit(&clkit, &settings) == RT_FAIL)
		return ;

	if (set_kernel_args(*(clkit.kernels), clkit.mems, &settings) == RT_FAIL)
		return ;

	enqueue_ndrange_kernel(*(clkit.cmd_queues), *(clkit.kernels),
		settings.window_width * settings.window_height);

	enqueue_read_buffer(*(clkit.cmd_queues),
		clkit.mems[RT_CL_MEM_IMAGE], settings.img_buf, &settings);

	execute_cmd_queue(*(clkit.cmd_queues));

	release(&clkit);
	clear_global_settings(&settings);

	mlx_put_image_to_window(
		dispatcher.marker.p_mlx,
		dispatcher.marker.p_win,
		dispatcher.marker.p_img, 0, 0);
	mlx_loop(dispatcher.p_mlx);
}
