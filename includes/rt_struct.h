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
typedef struct				s_light_wrapper
{
	void		*light;
	t_vec4		i_d;
	t_vec4		i_s;
	t_vec4		(*get_light_direction)(
		void *light,
		t_vec4 *point
	);
}							t_light_wrapper;

typedef struct				s_distant_light
{
	t_vec4		d;
}							t_distant_light;

typedef struct				s_object_commons
{
	int			specular_alpha;
	float		reflectivity;
	float		transparency;
	float		ior;
	t_vec4		k_a;
	t_vec4		k_d;
	t_vec4		k_s;
}							t_object_commons;

typedef struct				s_sphere
{
	float				r;
	t_vec4				c;
	t_object_commons	commons;
}							t_sphere;

typedef struct				s_triangle
{
	t_vec4				a;
	t_vec4				u;
	t_vec4				v;
	t_vec4				n;
	t_object_commons	commons;
}							t_triangle;

typedef struct				s_plane
{
	t_vec4				p;
	t_vec4				n;
	t_object_commons	commons;
}							t_plane;

typedef struct				s_disk
{
	float				r;
	t_plane				plane;
	t_object_commons	commons;
}							t_disk;

typedef struct 				s_cone
{
	float				theta;
	float				h;
	float				cos_2_theta;
	t_vec4				c;
	t_vec4				v;
	t_object_commons	commons;
}							t_cone;

typedef struct				s_cone_intersect_coefficients
{
	float				a;
	float				b;
	float				c;
	t_object_commons	commons;
}							t_cone_intersect_coefficients;

typedef struct 				s_cylinder
{
	float				r;
	float				h;
	t_vec4				c;
	t_vec4				c_rotated;
	t_vec4				v;
	t_quaternion		q;
	t_quaternion		q_i;
	t_object_commons	commons;
}							t_cylinder;

typedef struct				s_cylinder_intersect_coefficients
{
	float		a;
	float		b;
	float		c;
}							t_cylinder_intersect_coefficients;

typedef struct				s_trace_record
{
	t_vec4					point;
	t_vec4					normal;
	t_ray					*ray;
	// t_object_wrapper		*object_wrapper;
	struct s_trace_record	*prev;
}							t_trace_record;

typedef struct				s_global_settings
{
	int						window_width;
	int						window_height;
	int						num_objects;
	int						num_lights;
	size_t					objects_buf_size;
	t_ray_grid_properties	ray_grid_props;
	int						*img_buf;
	char					*kernel_name;
	char					*objects_buf;
	t_light_wrapper			*light_wrappers;
}							t_global_settings;

#endif