#include "rt.h"

static t_vec4		sphere_normal(void *object, t_vec4 *point)
{
	t_vec4		n;

	n = vec_sub_vec(point, &(((t_sphere *)object)->c));
	return (normalize(&n));
}

static float		get_t(float d_ce, float d_d, float det)
{
	float		t[2];
	int			i;

	t[0] = (-1 * d_ce - sqrt(det)) / d_d;
	t[1] = (-1 * d_ce + sqrt(det)) / d_d;
	i = 0;
	while (i < 2)
	{
		if (t[i] >= 0.0f)
			return (t[i]);
		i++;
	}
	return (-1.0f);
}

static int			sphere_intersect(
	void *object,
	t_ray *ray,
	float *t
)
{
	t_sphere	*sphere;
	t_vec4		ce;
	float		d_ce;
	float		d_d;
	float		det;
	
	sphere = (t_sphere *)object;
	ce = vec_sub_vec(&(ray->e), &(sphere->c));
	d_ce = vec_dot_vec(&(ray->d), &ce);
	d_d = vec_dot_vec(&(ray->d), &(ray->d));
	det = d_ce * d_ce - d_d * (vec_dot_vec(&ce, &ce) - sphere->r * sphere->r);
	if (det < 0.0f)
		return (RT_FALSE);
	*t = get_t(d_ce, d_d, det);
	if (*t < 0.0f)
		return (RT_FALSE);
	return (RT_TRUE);
}

t_object_wrapper	new_sphere(
	t_new_object_args *args_obj,
	t_new_sphere_args *args_sphere
)
{
	t_object_wrapper	object_wrapper;
	t_sphere			*sphere;

	object_wrapper.object = ft_memalloc(sizeof(t_sphere));
	if (object_wrapper.object == NULL)
		handle_memalloc_err("sphere");
	set_new_object(&object_wrapper, args_obj,
		&sphere_intersect, &sphere_normal);
	sphere = (t_sphere *)object_wrapper.object;
	sphere->c = args_sphere->c;
	sphere->r = args_sphere->r;
	return (object_wrapper);
}