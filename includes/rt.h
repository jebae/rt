#ifndef RT_H
# define RT_H

# include "gmath.h"
# include "rt_struct.h"
# include "rt_args.h"
# include <stdio.h> // remove after

# define RT_SUCCESS					1
# define RT_FAIL					0
# define RT_TRUE					1
# define RT_FALSE					0
# define RT_BACKGROUND_COLOR		0
# define RT_BIAS					1e-3
# define RT_DEPTH_LIMIT				5
# define RT_RAY_TYPE_NONE			0
# define RT_RAY_TYPE_REFLECTION		1
# define RT_RAY_TYPE_REFRACTION		2
# define RT_OBJECT_TYPE_SPHERE		0
# define RT_OBJECT_TYPE_CONE		1

typedef enum				e_rgb_shades_idx
{
	AMBIENT,
	DIFFUSE,
	SPECULAR,
	REFLECT,
	REFRACT,
}							t_rgb_shades_idx;

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
t_vec4						hit_point(t_ray *ray, float t);
int							trace(
	t_ray *ray,
	t_trace_record *prev_rec,
	t_trace_record *rec,
	t_global_settings *args
);

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
t_vec4						plane_normal(
	void *object,
	t_vec4 *point
);
t_object_wrapper			new_disk(
	t_new_object_args *args_obj,
	t_new_disk_args *args_disk
);
t_object_wrapper			new_cone(
	t_new_object_args *args_obj,
	t_new_cone_args *args_cone
);
t_object_wrapper			new_cylinder(
	t_new_object_args *args_obj,
	t_new_cylinder_args *args_cylinder
);
void						cylinder_get_coefficients(
	t_cylinder_intersect_coefficients *coeffs,
	t_cylinder *cylinder,
	t_ray *ray
);
t_ray						cylinder_rotate_ray(t_cylinder *cylinder, t_ray *ray);
t_ray						cylinder_stay_ray(t_cylinder *cylinder, t_ray *ray);
t_ray						cylinder_reverse_z_ray(t_cylinder *cylinder, t_ray *ray);

/*
** shading
*/
int							rgb_to_int(t_vec4 rgb_ratio);
t_vec4						ambient(t_vec4 *i_a, t_vec4 *k_a);
void						diffuse_specular(
	t_trace_record *rec,
	t_light_wrapper *light_wrapper,
	t_vec4 *rgb_shades
);
t_vec4						ray_color(
	t_trace_record *rec,
	int depth,
	t_global_settings *args
);
t_ray						get_reflect_ray(t_trace_record *rec);
t_vec4						reflection(
	t_trace_record *rec_origin,
	int depth,
	t_global_settings *args
);
t_vec4						refraction(
	t_trace_record *rec_origin,
	int refract_count,
	t_global_settings *args
);

/*
** shadow
*/
float						get_transmittance(
	t_trace_record *rec,
	t_light_wrapper *light_wrapper,
	t_object_wrapper *object_wrappers,
	int num_objects
);

/*
** utils
*/
void						exit_with_memalloc_err(const char *msg);

#endif