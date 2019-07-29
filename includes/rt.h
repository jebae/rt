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

# define RT_BACKGROUND_COLOR		0x000000
# define RT_BIAS					1e-3
# define RT_DEPTH_LIMIT				5

# define RT_RAY_TYPE_NONE			0
# define RT_RAY_TYPE_REFLECTION		1
# define RT_RAY_TYPE_REFRACTION		2

# define RT_OBJECT_TYPE_SPHERE		0
# define RT_OBJECT_TYPE_CONE		1
# define RT_OBJECT_TYPE_PLANE		2
# define RT_OBJECT_TYPE_TRIANGLE	3
# define RT_OBJECT_TYPE_CYLINDER	4

# define RT_LIGHT_TYPE_DISTANT		0
# define RT_LIGHT_TYPE_SPHERICAL	1

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

/*
** light
*/
size_t						new_distant_light(
	t_light_commons commons,
	t_new_distant_light_args *args_light,
	char *lights_buf
);

size_t						new_spherical_light(
	t_light_commons commons,
	t_new_spherical_light_args *args_light,
	char *lights_buf
);

t_vec4						distant_light_direction(void *light, t_vec4 *point);

/*
** object
*/
void						write_mem_buf(
	char *buf,
	char *content,
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

size_t						new_plane(
	t_object_commons commons,
	t_new_plane_args *args_plane,
	char *objects_buf
);

size_t						new_triangle(
	t_object_commons commons,
	t_new_triangle_args *args_triangle,
	char *objects_buf
);

size_t						new_cylinder(
	t_object_commons commons,
	t_new_cylinder_args *args_cylinder,
	char *objects_buf
);

/*
** utils
*/
void						exit_with_memalloc_err(const char *msg);

void						clear_global_settings(t_global_settings *settings);

#endif
