#include "rt.h"

static t_vec4			cylinder_normal(
	void *object,
	t_vec4 *point
)
{
	t_vec4			cp;
	t_vec4			n;
	t_cylinder		*cylinder;

	cylinder = (t_cylinder *)object;
	cp = vec_sub_vec(point, &(cylinder->c));
	n = scalar_mul_vec(vec_dot_vec(&cp, &(cylinder->v)), &(cylinder->v));
	n = vec_sub_vec(&cp, &n);
	return (normalize(&n));
}

static float			get_t(
	t_cylinder_intersect_coefficients *coeffs,
	float det,
	t_cylinder *cylinder,
	t_ray *ray
)
{
	int			i;
	float		t[2];
	t_vec4		p;

	t[0] = (-1.0f * coeffs->b - sqrtf(det)) / coeffs->a;
	t[1] = (-1.0f * coeffs->b + sqrtf(det)) / coeffs->a;
	if (coeffs->a < 0.0f)
		ft_swap(&(t[0]), &(t[1]), sizeof(float));
	i = 0;
	while (i < 2)
	{
		if (t[i] >= 0.0f)
		{
			p = hit_point(ray, t[i]);
			if (p.arr[2] - cylinder->c_rotated.arr[2] >= 0.0f &&\
				p.arr[2] - cylinder->c_rotated.arr[2] <= cylinder->h)
				return (t[i]);
		}
		i++;
	}
	return (-1.0f);
}

static int				cylinder_intersect(
	void *object,
	t_ray *ray,
	float *t
)
{
	float								det;
	t_cylinder							*cylinder;
	t_cylinder_intersect_coefficients	coeffs;
	t_ray								ray_rotated;

	cylinder = (t_cylinder *)object;
	ray_rotated = cylinder->rotate_ray(cylinder, ray);
	cylinder_get_coefficients(&coeffs, cylinder, &ray_rotated);
	det = coeffs.b * coeffs.b - coeffs.a * coeffs.c;
	if (det < 0.0f)
		return (RT_FALSE);
	*t = get_t(&coeffs, det, cylinder, &ray_rotated);
	if (*t < 0.0f)
		return (RT_FALSE);
	return (RT_TRUE);
}

static void				set_cylinder_rotate_q(t_cylinder *cylinder)
{
	static t_vec4		z_axis = (t_vec4){{0.0f, 0.0f, 1.0f, 1.0f}};
	float				theta;
	t_vec4				axis;

	theta = vec_dot_vec(&(cylinder->v), &z_axis);
	if (theta >= 1.0f)
	{
		cylinder->rotate_ray = &cylinder_stay_ray;
		cylinder->c_rotated = cylinder->c;
		return ;
	}
	else if (theta <= -1.0f)
	{
		cylinder->rotate_ray = &cylinder_reverse_z_ray;
		cylinder->c_rotated = cylinder->c;
		cylinder->c_rotated.arr[2] = -1.0f * cylinder->c_rotated.arr[2];
		return ;
	}
	theta = acosf(theta);
	axis = vec_cross_vec(&(cylinder->v), &z_axis);
	axis = normalize(&axis);
	cylinder->q = rotate_q(&axis, theta);
	cylinder->q_i = inverse_q(&(cylinder->q));
	cylinder->rotate_ray = &cylinder_rotate_ray;
	cylinder->c_rotated = rotate(&(cylinder->q), &(cylinder->c), &(cylinder->q_i));
}

t_object_wrapper		new_cylinder(
	t_new_object_args *args_obj,
	t_new_cylinder_args *args_cylinder
)
{
	t_object_wrapper	object_wrapper;
	t_cylinder			*cylinder;

	object_wrapper.object = ft_memalloc(sizeof(t_cylinder));
	if (object_wrapper.object == NULL)
		handle_memalloc_err("cylinder");
	set_new_object(&object_wrapper, args_obj,
		&cylinder_intersect, &cylinder_normal);
	cylinder = (t_cylinder *)object_wrapper.object;
	cylinder->r = args_cylinder->r;
	cylinder->h = args_cylinder->h;
	cylinder->c = args_cylinder->c;
	cylinder->v = normalize(&(args_cylinder->v));
	set_cylinder_rotate_q(cylinder);
	return (object_wrapper);
}