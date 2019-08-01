/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_args.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:06:53 by jebae             #+#    #+#             */
/*   Updated: 2019/08/01 17:08:24 by jebae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
}							t_set_ray_grid_properties_args;

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

typedef struct				s_new_cone_args
{
	float		theta;
	float		h;
	t_vec4		c;
	t_vec4		v;
}							t_new_cone_args;

typedef struct				s_new_cylinder_args
{
	float		r;
	float		h;
	t_vec4		c;
	t_vec4		v;
}							t_new_cylinder_args;

typedef struct				s_new_distant_light_args
{
	t_vec4		d;
}							t_new_distant_light_args;

typedef struct				s_new_spherical_light_args
{
	t_vec4		origin;
}							t_new_spherical_light_args;

typedef struct				s_global_settings_args
{
	int						window_width;
	int						window_height;
	int						num_objects;
	int						num_lights;
	size_t					objects_buf_size;
	size_t					lights_buf_size;
	t_ray_grid_properties	ray_grid_props;
	t_vec4					i_a;
}							t_global_settings_args;

#endif
