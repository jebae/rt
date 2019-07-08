#include "rt.h"

static t_ray_grid_properties	cal_ray_grid_properties(
	t_set_ray_grid_properties_args *args
)
{
	t_ray_grid_properties		props;
	float						g_x;
	float						g_y;

	g_x = tan(args->aov / 2.0f);
	g_y = g_x * args->height / args->width;
	props.dx = scalar_mul_vec(g_x, &(args->x));
	props.dy = scalar_mul_vec(g_y, &(args->y));
	props.offset = vec_sub_vec(&(args->z), &(props.dx));
	props.offset = vec_sub_vec(&(props.offset), &(props.dy));
	props.dx = scalar_mul_vec(2.0f / (args->width - 1.0f), &(props.dx));
	props.dy = scalar_mul_vec(2.0f / (args->height - 1.0f), &(props.dy));
	props.e = args->cam->pos;
	return (props);
}

t_ray_grid_properties			get_ray_grid_properties(
	t_camera *cam,
	float width,
	float height,
	float aov
)
{
	static t_vec4						z_w = (t_vec4){{0, 0, 1, 1}};
	t_set_ray_grid_properties_args		args;

	args.width = width;
	args.height = height;
	args.aov = aov;
	args.z = camera_z_axis(cam);
	args.x = camera_x_axis(&z_w, &(args.z), cam->roll);
	args.y = camera_y_axis(&(args.z), &(args.x));
	args.cam = cam;
	return (cal_ray_grid_properties(&args));
}