#include "rt_test.h"

static float		WIDTH = 1000;
static float		HEIGHT = 800;

static t_camera		get_cam(void)
{
	t_camera	cam;
	t_vec4		focus;

	focus = (t_vec4){{0, 0, 0, 1}};
	cam.pos = (t_vec4){{1, 1, 1, 1}};
	cam.roll = 0;
	set_camera_axis(&cam, &focus);
	return (cam);
}

static void			render_ray_direction(
	t_ray_grid_properties *props,
	t_camera *cam
)
{
	t_test_dispatcher	dispatcher;
	t_global_settings	settings;
	t_coord				p1;
	t_coord				p2;
	t_mat4				mat;
	t_ray				ray;

	init_mlx(&dispatcher, WIDTH, HEIGHT);
	init_marker(&(dispatcher.marker), dispatcher.p_mlx, dispatcher.p_win, &settings);
	mat = world_to_cam_coord_mat(cam);
	dispatcher.marker.color = 0xFFFFFF;
	for (int i=0; i <= HEIGHT; i += 100)
	{
		for (int j=0; j <= WIDTH; j += 10)
		{
			set_ray(props, &ray, j, i);
			ray.e = mat_mul_vec(&mat, &(ray.e));
			ray.d = mat_mul_vec(&mat, &(ray.d));
			p1.x = ray.e.arr[0] + WIDTH / 2.0f;
			p1.y = ray.e.arr[1] + HEIGHT / 2.0f;
			p2.x = ray.d.arr[0] + WIDTH / 2.0f;
			p2.y = ray.d.arr[1] + HEIGHT / 2.0f;
			plot_line(&p1, &p2, NULL, &(dispatcher.marker));
		}
	}
	mlx_loop(dispatcher.p_mlx);
}

void				test_ray_direction(void)
{
	t_ray_grid_properties		props;
	t_camera					cam;

	cam = get_cam();
	props = get_ray_grid_properties(&cam, WIDTH, HEIGHT, M_PI / 2);
	cam.zoom = ABS(WIDTH / (props.offset.arr[0] * 20));
	render_ray_direction(&props, &cam);
}
