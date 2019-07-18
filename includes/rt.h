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
void						write_object(
	char *objects_buf,
	char *object,
	size_t size,
	int type
);

size_t						new_sphere(
	t_object_commons commons,
	t_new_sphere_args *args_sphere,
	char *objects_buf
);

size_t						new_cone(
	t_object_commons commons,
	t_new_cone_args *args_cone,
	char *objects_buf
);

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
// float						get_transmittance(
// 	t_trace_record *rec,
// 	t_light_wrapper *light_wrapper,
// 	t_object_wrapper *object_wrappers,
// 	int num_objects
// );

/*
** utils
*/
void						exit_with_memalloc_err(const char *msg);

void						clear_global_settings(t_global_settings *settings);

#endif