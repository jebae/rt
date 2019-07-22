#ifndef RT_STRUCT_H
# define RT_STRUCT_H

# include "gmath.h"

typedef struct				s_color
{
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
}							t_color;

typedef struct				s_ray
{
	int				type;
	float			ior_medium;
	t_vec4			e;
	t_vec4			d;
}							t_ray;

typedef struct				s_ray_grid_properties
{
	t_vec4		e;
	t_vec4		offset;
	t_vec4		dx;
	t_vec4		dy;
}							t_ray_grid_properties;

/*
** think about add light color later
*/
typedef struct				s_light_commons
{
	t_vec4		intensity;
}							t_light_commons;

typedef struct				s_distant_light
{
	t_light_commons		commons;
	t_vec4				d;
}							t_distant_light;

typedef struct				s_object_commons
{
	int			specular_alpha;
	float		reflectivity;
	float		transparency;
	float		ior;
	t_vec4		color;
}							t_object_commons;

typedef struct				s_sphere
{
	t_object_commons	commons;
	float				r;
	t_vec4				c;
}							t_sphere;

typedef struct				s_triangle
{
	t_object_commons	commons;
	t_vec4				a;
	t_vec4				u;
	t_vec4				v;
	t_vec4				n;
}							t_triangle;

typedef struct				s_plane
{
	t_object_commons	commons;
	t_vec4				p;
	t_vec4				n;
}							t_plane;

typedef struct				s_disk
{
	t_object_commons	commons;
	float				r;
	t_plane				plane;
}							t_disk;

typedef struct 				s_cone
{
	t_object_commons	commons;
	float				theta;
	float				h;
	float				cos_2_theta;
	t_vec4				c;
	t_vec4				v;
}							t_cone;

typedef struct				s_cone_intersect_coefficients
{
	float				a;
	float				b;
	float				c;
}							t_cone_intersect_coefficients;

typedef struct 				s_cylinder
{
	t_object_commons	commons;
	float				r;
	float				h;
	t_vec4				c;
	t_vec4				v;
}							t_cylinder;

typedef struct				s_cylinder_intersect_coefficients
{
	float		a;
	float		b;
	float		c;
}							t_cylinder_intersect_coefficients;

typedef struct				s_global_settings
{
	int						window_width;
	int						window_height;
	int						num_objects;
	int						num_lights;
	size_t					objects_buf_size;
	size_t					lights_buf_size;
	t_ray_grid_properties	ray_grid_props;
	t_vec4					i_a;
	int						*img_buf;
	char					*kernel_name;
	char					*objects_buf;
	char					*lights_buf;
}							t_global_settings;

#endif