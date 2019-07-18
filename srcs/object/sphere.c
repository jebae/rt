#include "rt.h"

// static t_vec4		sphere_normal(
// 	void *object,
// 	t_vec4 *point
// )
// {
// 	t_vec4		n;

// 	n = vec_sub_vec(point, &(((t_sphere *)object)->c));
// 	return (normalize(&n));
// }

// static float		get_t(float d_ce, float d_d, float det)
// {
// 	int			i;
// 	float		t[2];

// 	t[0] = (-1.0f * d_ce - sqrtf(det)) / d_d;
// 	t[1] = (-1.0f * d_ce + sqrtf(det)) / d_d;
// 	if (d_d < 0.0f)
// 		ft_swap(&(t[0]), &(t[1]), sizeof(float));
// 	i = 0;
// 	while (i < 2)
// 	{
// 		if (t[i] >= 0.0f)
// 			return (t[i]);
// 		i++;
// 	}
// 	return (-1.0f);
// }

// static int			sphere_intersect(
// 	void *object,
// 	t_ray *ray,
// 	float *t
// )
// {
// 	t_sphere	*sphere;
// 	t_vec4		ce;
// 	float		d_ce;
// 	float		d_d;
// 	float		det;

// 	sphere = (t_sphere *)object;
// 	ce = vec_sub_vec(&(ray->e), &(sphere->c));
// 	d_ce = vec_dot_vec(&(ray->d), &ce);
// 	d_d = vec_dot_vec(&(ray->d), &(ray->d));
// 	det = d_ce * d_ce - d_d * (vec_dot_vec(&ce, &ce) - sphere->r * sphere->r);
// 	if (det < 0.0f)
// 		return (RT_FALSE);
// 	*t = get_t(d_ce, d_d, det);
// 	if (*t < 0.0f)
// 		return (RT_FALSE);
// 	return (RT_TRUE);
// }

size_t		new_sphere(
	t_object_commons commons,
	t_new_sphere_args *args_sphere,
	char *objects_buf
)
{
	t_sphere			sphere;

	sphere.commons = commons;
	sphere.c = args_sphere->c;
	sphere.r = args_sphere->r;
	write_object(objects_buf, (char *)&sphere, sizeof(sphere), RT_OBJECT_TYPE_SPHERE);
	return (sizeof(sphere) + sizeof(int));
}