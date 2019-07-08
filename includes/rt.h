#ifndef RT_H
# define RT_H

# include "gmath.h"
# include "rt_struct.h"
# include "rt_args.h"
# include <stdio.h> // remove after

# define RT_TRUE			1
# define RT_FALSE			0

/*
** ray
*/
t_ray_grid_properties		get_ray_grid_properties(
	t_camera *cam,
	float width,
	float height,
	float aov
);

void						set_ray(
	t_ray_grid_properties *props,
	t_ray *ray,
	int scalar_x,
	int scalar_y
);

t_vec4						intersection_point(t_ray *ray, float t);

/*
** light
*/
t_light_wrapper				new_distant_light(
	t_new_light_args *args_light,
	t_new_distant_light_args *args_distant
);
t_vec4						distant_light_direction(void *light, t_vec4 *point);

/*
** object
*/
void						set_new_object(
	t_object_wrapper *object_wrapper,
	t_new_object_args *args,
	int (*intersect)(void *, t_ray *, float *),
	t_vec4 (*get_normal)(void *, t_vec4 *)
);
t_object_wrapper			new_sphere(
	t_new_object_args *args_obj,
	t_new_sphere_args *args_sphere
);
t_object_wrapper			new_triangle(
	t_new_object_args *args_obj,
	t_new_triangle_args *args_triangle
);
t_object_wrapper			new_plane(
	t_new_object_args *args_obj,
	t_new_plane_args *args_plane
);
int							plane_intersect(
	void *object,
	t_ray *ray,
	float *t
);
t_vec4						plane_normal(void *object, t_vec4 *point);
t_object_wrapper			new_disk(
	t_new_object_args *args_obj,
	t_new_disk_args *args_disk
);
t_object_wrapper			new_cone(
	t_new_object_args *args_obj,
	t_new_cone_args *args_cone
);

/*
** shading
*/
int							cal_color(t_vec4 rgb_ratio);
t_vec4						ambient(t_vec4 *i_a, t_vec4 *k_a);
t_vec4						diffuse_specular(t_diffuse_specular_args *args);

/*
** utils
*/
void						handle_memalloc_err(const char *msg);

#endif