#include "rt.h"

static t_vec4		diffuse(float n_l, t_vec4 *i_d, t_vec4 *k_d)
{
	int			i;
	t_vec4		res;

	i = 0;
	while (i < 3)
	{
		res.arr[i] = i_d->arr[i] * k_d->arr[i] * n_l;
		i++;
	}
	return (res);
}

static t_vec4		specular(
	t_vec4 *r,
	t_vec4 *ray_d,
	t_object_wrapper *object_wrapper,
	t_light_wrapper *light_wrapper
)
{
	int			i;
	float		r_v;
	t_vec4		res;

	r_v = -1.0f * vec_dot_vec(r, ray_d);
	r_v = MAX(0.0f, r_v);
	r_v = pow(r_v, object_wrapper->specular_alpha);
	i = 0;
	while (i < 3)
	{
		res.arr[i] = light_wrapper->i_s.arr[i] *
			object_wrapper->k_s.arr[i] * r_v;
		i++;
	}
	return (res);
}

t_vec4				diffuse_specular(
	t_vec4 *ray_d,
	t_trace_record *rec,
	t_light_wrapper *light_wrapper
)
{
	t_vec4						r;
	t_vec4						l;
	t_vec4						d;
	t_vec4						s;
	float						n_l;

	l = light_wrapper->get_light_direction(
		light_wrapper->light, &(rec->point));
	n_l = -1.0f * vec_dot_vec(&(rec->normal), &l);
	n_l = MAX(0.0f, n_l);
	d = diffuse(n_l, &(light_wrapper->i_d), &(rec->object_wrapper->k_d));
	r = scalar_mul_vec(2.0f * n_l, &(rec->normal));
	r = vec_plus_vec(&l, &r);
	s = specular(&r, ray_d, rec->object_wrapper, light_wrapper);
	// return (d);
	return (vec_plus_vec(&d, &s));
}