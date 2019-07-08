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
	t_vec4		e;
	t_vec4		d;
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

typedef struct				s_object_wrapper
{
	void		*object;
	t_vec4		k_a;
	t_vec4		k_d;
	t_vec4		k_s;
	int			shine;
	int			(*intersect)(
		void *object,
		t_ray *ray,
		float *t
	);
	t_vec4		(*get_normal)(
		void *object,
		t_vec4 *point
	);
}							t_object_wrapper;

typedef struct				s_sphere
{
	float		r;
	t_vec4		c;
}							t_sphere;

typedef struct				s_triangle
{
	t_vec4		a;
	t_vec4		u;
	t_vec4		v;
	t_vec4		n;
}							t_triangle;

typedef struct				s_plane
{
	t_vec4		p;
	t_vec4		n;
}							t_plane;

typedef struct				s_disk
{
	float		r;
	t_plane		plane;
}							t_disk;

typedef struct 				s_cone
{
	float		theta;
	float		h;
	float		cos_2_theta;
	t_vec4		c;
	t_vec4		v;
}							t_cone;

#endif