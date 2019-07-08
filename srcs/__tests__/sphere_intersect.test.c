#include "rt_test.h"

static float		WIDTH = 1000;
static float		HEIGHT = 600;

static t_ray_grid_properties	get_ray_grid_props_for_test(void)
{
	t_ray_grid_properties	props;
	t_camera				cam;

	cam.focus = (t_vec4){{0, 0, 0, 1}};
	cam.pos = (t_vec4){{10, 10, 10, 1}};
	cam.roll = 0;
	props = get_ray_grid_properties(&cam, WIDTH, HEIGHT, M_PI / 2.0f);
	return (props);
}

static void						render_sphere_intersection(
	t_ray_grid_properties *props,
	t_object_wrapper *object_wrapper
)
{
	t_test_dispatcher	dispatcher;
	t_ray				ray;
	t_coord				p;
	float				t;

	init_mlx(&dispatcher, WIDTH, HEIGHT);
	init_marker(&(dispatcher.marker), dispatcher.p_mlx, dispatcher.p_win);
	dispatcher.marker.color = 0x008800;
	for (int i=0; i < HEIGHT; i++)
	{
		for (int j=0; j < WIDTH; j++)
		{
			set_ray(props, &ray, j, i);
			if (object_wrapper->intersect(object_wrapper->object, &ray, &t) == RT_TRUE)
			{
				p.x = j;
				p.y = i;
				dispatcher.marker.mark_pixel(&(dispatcher.marker), &p, NULL);
			}
		}
	}
	ft_memdel((void **)&(object_wrapper->object));
	mlx_loop(dispatcher.p_mlx);
}

void							test_sphere_intersect(void)
{
	t_ray_grid_properties		props;
	t_object_wrapper			object_wrapper;
	t_new_sphere_args			args_sphere;
	t_new_object_args			args_obj;

	props = get_ray_grid_props_for_test();
	args_sphere.r = 2;
	args_sphere.c = (t_vec4){{3, 3, 3, 1}};
	object_wrapper = new_sphere(&args_obj, &args_sphere);
	render_sphere_intersection(&props, &object_wrapper);
}