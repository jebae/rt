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

	focus = (t_vec4){{0.0f, 1.0f, 1.0f, 1}};
	cam.pos = (t_vec4){{0.0f, 0.0f, 1.0f, 1}};
	cam.roll = 0;
	set_camera_axis(&cam, &focus);
	props = get_ray_grid_properties(&cam, WIDTH, HEIGHT, M_PI / 2.0f);
	return (props);
}

static size_t		get_distant_light(char *lights_buf)
{
	t_new_distant_light_args	args_light;
	t_light_commons				commons;

	commons.intensity = (t_vec4){{0.5f, 0.5f, 0.5f}};
	args_light.d = (t_vec4){{0.0f, 1.0f, -2.0f, 1}};
	return (new_distant_light(commons, &args_light, lights_buf));
}

static size_t		get_bulb_light(char *lights_buf)
{
	t_new_spherical_light_args		args_light; t_light_commons					commons;

	commons.intensity = (t_vec4){{30.0f, 30.0f, 30.0f}};
	args_light.origin = (t_vec4){{1.0f, 10.0f, 4.0f, 1}};
	return (new_spherical_light(commons, &args_light, lights_buf));
}

static size_t		get_bulb_glass(char *objects_buf)
{
	t_new_sphere_args			args_sphere;
	t_object_commons			commons;

	commons.specular_alpha = 1;
	commons.reflectivity = 0.2f;
	commons.transparency = 0.8f;
	commons.ior = 1.5f;
	commons.color = (t_vec4){{0.9f, 0.6f, 0.1f, 1}};
	args_sphere.r = 1.0f;
	args_sphere.c = (t_vec4){{1.0f, 10.0f, 4.0f, 1}};
	return (new_sphere(commons, &args_sphere, objects_buf));
}

static size_t		get_bulb_hat(char *objects_buf)
{
	t_new_cone_args				args_cone;
	t_object_commons			commons;

	commons.specular_alpha = 50;
	commons.reflectivity = 0.2f;
	commons.transparency = 0.0f;
	commons.ior = 1.5f;
	commons.color = (t_vec4){{0.1f, 0.1f, 0.1f, 1}};
	args_cone.theta = M_PI / 5.0f;
	args_cone.h = 2.5f;
	args_cone.c = (t_vec4){{1.7f, 10.2f, 6.0f, 1.0f}};
	args_cone.v = (t_vec4){{-1.0f, -0.0f, -3.0f, 1.0f}};
	return (new_cone(commons, &args_cone, objects_buf));
}

static size_t		get_stand_neck1(char *objects_buf)
{
	t_new_cylinder_args			args_cylinder;
	t_object_commons			commons;

	commons.specular_alpha = 50;
	commons.reflectivity = 0.0f;
	commons.transparency = 0.0f;
	commons.ior = 1.5f;
	commons.color = (t_vec4){{1.0f, 1.0f, 0.9f, 1}};
	args_cylinder.r = 0.2f;
	args_cylinder.h = 7.0f;
	args_cylinder.c = (t_vec4){{1.7f, 10.3f, 5.9f, 1.0f}};
	args_cylinder.v = (t_vec4){{1.0f, 0.5f, -0.3f, 1.0f}};
	return (new_cylinder(commons, &args_cylinder, objects_buf));
}

static size_t		get_stand_neck2(char *objects_buf)
{
	t_new_cylinder_args			args_cylinder;
	t_object_commons			commons;

	commons.specular_alpha = 50;
	commons.reflectivity = 0.0f;
	commons.transparency = 0.0f;
	commons.ior = 1.5f;
	commons.color = (t_vec4){{1.0f, 1.0f, 0.9f, 1}};
	args_cylinder.r = 0.2f;
	args_cylinder.h = 5.0f;
	args_cylinder.c = (t_vec4){{1.7f, 10.3f, 5.9f, 1.0f}};
	args_cylinder.v = (t_vec4){{1.0f, 0.5f, -0.8f, 1.0f}};
	return (new_cylinder(commons, &args_cylinder, objects_buf));
}

static size_t		get_stand_leg1(char *objects_buf)
{
	t_new_cylinder_args			args_cylinder;
	t_object_commons			commons;

	commons.specular_alpha = 50;
	commons.reflectivity = 0.0f;
	commons.transparency = 0.0f;
	commons.ior = 1.5f;
	commons.color = (t_vec4){{1.0f, 1.0f, 0.9f, 1}};
	args_cylinder.r = 0.2f;
	args_cylinder.h = 6.0f;
	args_cylinder.c = (t_vec4){{8.2f, 13.5f, 3.9f, 1.0f}};
	args_cylinder.v = (t_vec4){{-1.1f, 0.5f, -2.0f, 1.0f}};
	return (new_cylinder(commons, &args_cylinder, objects_buf));
}

static size_t		get_stand_leg2(char *objects_buf)
{
	t_new_cylinder_args			args_cylinder;
	t_object_commons			commons;

	commons.specular_alpha = 50;
	commons.reflectivity = 0.0f;
	commons.transparency = 0.0f;
	commons.ior = 1.5f;
	commons.color = (t_vec4){{1.0f, 1.0f, 0.9f, 1}};
	args_cylinder.r = 0.2f;
	args_cylinder.h = 5.0f;
	args_cylinder.c = (t_vec4){{5.3f, 12.11f, 2.9f, 1.0f}};
	args_cylinder.v = (t_vec4){{-0.1f, 0.5f, -1.0f, 1.0f}};
	return (new_cylinder(commons, &args_cylinder, objects_buf));
}

static size_t		get_stand_foot(char *objects_buf)
{
	t_new_sphere_args			args_sphere;
	t_object_commons			commons;

	commons.specular_alpha = 1;
	commons.reflectivity = 0.05f;
	commons.transparency = 0.0f;
	commons.ior = 1.5f;
	commons.color = (t_vec4){{0.4f, 0.8f, 0.7f, 1}};
	args_sphere.r = 2.0f;
	args_sphere.c = (t_vec4){{5.4f, 14.2f, -1.6f, 1}};
	return (new_sphere(commons, &args_sphere, objects_buf));
}

static size_t		get_ball(char *objects_buf)
{
	t_new_sphere_args			args_sphere;
	t_object_commons			commons;

	commons.specular_alpha = 1;
	commons.reflectivity = 0.1f;
	commons.transparency = 0.1f;
	commons.ior = 1.5f;
	commons.color = (t_vec4){{0.9f, 0.2f, 0.1f, 1}};
	args_sphere.r = 1.0f;
	args_sphere.c = (t_vec4){{0.0f, 9.0f, 0.0f, 1}};
	return (new_sphere(commons, &args_sphere, objects_buf));
}

static size_t		get_fanta(char *objects_buf)
{
	t_new_cylinder_args			args_cylinder;
	t_object_commons			commons;

	commons.specular_alpha = 50;
	commons.reflectivity = 0.2f;
	commons.transparency = 0.0f;
	commons.ior = 1.5f;
	commons.color = (t_vec4){{1.0f, 0.4f, 0.0f, 1}};
	args_cylinder.r = 0.7f;
	args_cylinder.h = 2.0f;
	args_cylinder.c = (t_vec4){{-3.5f, 7.0f, -0.3f, 1.0f}};
	args_cylinder.v = (t_vec4){{1.0f, -0.5f, 0.0f, 1.0f}};
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

static size_t		get_wall(char *objects_buf)
{
	t_new_plane_args			args_plane;
	t_object_commons			commons;

	commons.reflectivity = 0.0f;
	commons.transparency = 0.0f;
	commons.ior = 1.5;
	commons.color = (t_vec4){{0.3f, 0.7f, 0.6f, 1}};
	commons.specular_alpha = 50;
	args_plane.n = (t_vec4){{0.0f, -1.0f, 0.0f, 1}};
	args_plane.p = (t_vec4){{0.0f, 20.0f, 0.0f, 1}};
	return (new_plane(commons, &args_plane, objects_buf));
}
static void			write_objects(char *objects_buf)
{
	objects_buf += get_plane(objects_buf);
	objects_buf += get_wall(objects_buf);
	objects_buf += get_bulb_glass(objects_buf);
	objects_buf += get_bulb_hat(objects_buf);
	objects_buf += get_stand_neck1(objects_buf);
	objects_buf += get_stand_neck2(objects_buf);
	objects_buf += get_stand_leg1(objects_buf);
	objects_buf += get_stand_leg2(objects_buf);
	objects_buf += get_stand_foot(objects_buf);
	objects_buf += get_ball(objects_buf);
	objects_buf += get_fanta(objects_buf);
}

static void			write_lights(char *lights_buf)
{
	lights_buf += get_bulb_light(lights_buf);
	lights_buf += get_distant_light(lights_buf);
}

void				test_render_scene1(int parallel_mode)
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

	settings.num_objects = 11;
	buf_size = sizeof(t_sphere) +
		sizeof(t_sphere) +
		sizeof(t_sphere) +
		sizeof(t_plane) +
		sizeof(t_plane) +
		sizeof(t_cone) +
		sizeof(t_cylinder) +
		sizeof(t_cylinder) +
		sizeof(t_cylinder) +
		sizeof(t_cylinder) +
		sizeof(t_cylinder) +
		sizeof(int) * settings.num_objects;
	settings.objects_buf_size = buf_size;
	settings.objects_buf = (char *)ft_memalloc(buf_size);
	write_objects(settings.objects_buf);

	settings.num_lights = 2;
	buf_size = sizeof(t_spherical_light) + sizeof(t_distant_light) +
		sizeof(int) * settings.num_lights;
	settings.lights_buf_size = buf_size;
	settings.lights_buf = (char *)ft_memalloc(buf_size);
	write_lights(settings.lights_buf);

	init_clkit(&clkit, &settings);

	render_scene(&clkit, &settings);

	release(&clkit);
	clear_global_settings(&settings);

	mlx_put_image_to_window(
		dispatcher.marker.p_mlx,
		dispatcher.marker.p_win,
		dispatcher.marker.p_img, 0, 0);
	mlx_loop(dispatcher.p_mlx);
}
