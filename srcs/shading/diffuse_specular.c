#include "rt.h"

t_vec4		diffuse(float n_l, t_vec4 *i_d, t_vec4 *k_d)
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

t_vec4		specular(
	t_vec4 *r,
	t_diffuse_specular_args *args
)
{
	int			i;
	float		r_v;
	t_vec4		res;

	r_v = -1.0f * vec_dot_vec(r, args->ray_d);
	r_v = MAX(0.0f, r_v);
	r_v = pow(r_v, args->object_wrapper->shine);
	i = 0;
	while (i < 3)
	{
		res.arr[i] = args->light_wrapper->i_s.arr[i] *
			args->object_wrapper->k_s.arr[i] * r_v;
		i++;
	}
	return (res);
}

t_vec4		diffuse_specular(t_diffuse_specular_args *args)
{
	t_diffuse_specular_vecs		vecs;
	t_vec4						d;
	t_vec4						s;
	float						n_l;

	vecs.n = args->object_wrapper->get_normal(
		args->object_wrapper->object, args->point);
	vecs.l = args->light_wrapper->get_light_direction(
		args->light_wrapper->light, args->point);
	n_l = -1.0f * vec_dot_vec(&(vecs.n), &(vecs.l));
	n_l = MAX(0.0f, n_l);
	d = diffuse(n_l, &(args->light_wrapper->i_d), &(args->object_wrapper->k_d));
	vecs.r = scalar_mul_vec(2.0f * n_l, &(vecs.n));
	vecs.r = vec_plus_vec(&(vecs.l), &(vecs.r));
	s = specular(&(vecs.r), args);
	// return (s);
	return (vec_plus_vec(&d, &s));
}