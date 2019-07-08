#include "rt_test.h"

static float		WIDTH = 1000;
static float		HEIGHT = 600;

static t_ray_grid_properties	get_ray_grid_props_for_test(void)
{
	t_ray_grid_properties	props;
	t_camera				cam;

	cam.focus = (t_vec4){{0, 10, 10, 1}};
	cam.pos = (t_vec4){{10, 10, 10, 1}};
	cam.roll = 0;
	props = get_ray_grid_properties(&cam, WIDTH, HEIGHT, M_PI / 2.0f);
	return (props);
}

static void						render_plane_intersection(
	t_ray_grid_properties *props,
	t_object_wrapper *object_wrappers,
	int num_objects,
	int *colors
)
{
	float				t;
	t_coord				p;
	t_ray				ray;
	t_test_dispatcher	dispatcher;
	t_object_wrapper	*object_wrapper;

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
				dispatcher.marker.color = colors[k];
				p.x = j;
				p.y = i;
				dispatcher.marker.mark_pixel(&(dispatcher.marker), &p, NULL);
			}
		}
	}
	ft_memdel((void **)&(object_wrapper->object));
	mlx_loop(dispatcher.p_mlx);
}

void							test_plane_intersect(void)
{
	t_ray_grid_properties		props;
	t_object_wrapper			object_wrappers[3];
	t_new_plane_args			args_plane;
	t_new_object_args			args_obj;
	int							colors[3];

	props = get_ray_grid_props_for_test();
	colors[0] = 0x008800;
	args_plane.n = (t_vec4){{0, 0, 1, 1}};
	args_plane.p = (t_vec4){{0, 0, 0}};
	object_wrappers[0] = new_plane(&args_obj, &args_plane);
	colors[1] = 0x000088;
	args_plane.n = (t_vec4){{0, 0, -1, 1}};
	args_plane.p = (t_vec4){{0, 0, 20}};
	object_wrappers[1] = new_plane(&args_obj, &args_plane);
	colors[2] = 0x880000;
	args_plane.n = (t_vec4){{0, -1, 0, 1}};
	args_plane.p = (t_vec4){{0, 20, 0}};
	object_wrappers[2] = new_plane(&args_obj, &args_plane);
	render_plane_intersection(&props, object_wrappers,\
		sizeof(object_wrappers) / sizeof(t_object_wrapper), colors);
}