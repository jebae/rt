#ifndef RT_ARGS_H
# define RT_ARGS_H

# include "gmath.h"
# include "rt_struct.h"

typedef struct				s_set_ray_grid_properties_args
{
	t_camera	*cam;
	float		width;
	float		height;
	float		aov;
	t_vec4		x;
	t_vec4		y;
	t_vec4		z;
}							t_set_ray_grid_properties_args;

typedef struct				s_new_object_args
{
	int			specular_alpha;
	float		reflectivity;
	float		transparency;
	float		ior;
	t_vec4		k_a;
	t_vec4		k_d;
	t_vec4		k_s;
}							t_new_object_args;

typedef struct				s_new_sphere_args
{
	float		r;
	t_vec4		c;
}							t_new_sphere_args;

typedef struct				s_new_triangle_args
{
	t_vec4		a;
	t_vec4		u;
	t_vec4		v;
}							t_new_triangle_args;

typedef struct				s_new_plane_args
{
	t_vec4		p;
	t_vec4		n;
}							t_new_plane_args;

typedef struct				s_new_disk_args
{
	float		r;
	t_vec4		p;
	t_vec4		n;
}							t_new_disk_args;

typedef struct 				s_new_cone_args
{
	float		theta;
	float		h;
	t_vec4		c;
	t_vec4		v;
}							t_new_cone_args;

typedef struct 				s_new_cylinder_args
{
	float		r;
	float		h;
	t_vec4		c;
	t_vec4		v;
}							t_new_cylinder_args;

typedef struct				s_new_light_args
{
	t_vec4		i_d;
	t_vec4		i_s;
}							t_new_light_args;

typedef struct				s_new_distant_light_args
{
	t_vec4		d;
}							t_new_distant_light_args;

typedef struct				s_global_rt_args
{
	int					num_objects;
	int					num_lights;
	t_vec4				*i_a;
	t_object_wrapper	*object_wrappers;
	t_light_wrapper		*light_wrappers;
}							t_global_rt_args;

#endif