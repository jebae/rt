#include "rt.h"

static void				get_coefficients(
	t_cone_intersect_coefficients *coeffs,
	t_cone *cone,
	t_ray *ray
)
{
	float		ce_v;
	float		d_v;
	t_vec4		ce;

	ce = vec_sub_vec(&(ray->e), &(cone->c));
	ce_v = vec_dot_vec(&ce, &(cone->v));
	d_v = vec_dot_vec(&(ray->d), &(cone->v));
	coeffs->a = d_v * d_v - cone->cos_2_theta;
	coeffs->b = ce_v * d_v - vec_dot_vec(&(ray->d), &ce) * cone->cos_2_theta;
	coeffs->c = ce_v * ce_v - vec_dot_vec(&ce, &ce) * cone->cos_2_theta;
}

static float				get_t(
	t_cone_intersect_coefficients *coeffs,
	float det,
	t_cone *cone,
	t_ray *ray
)
{
	int			i;
	float		t[2];
	t_vec4		cp;

	t[0] = (-1 * coeffs->b - sqrt(det)) / coeffs->a;
	t[1] = (-1 * coeffs->b + sqrt(det)) / coeffs->a;
	i = 0;
	while (i < 2)
	{
		if (t[i] > 0.0f)
		{
			cp = intersection_point(ray, t[i]);
			cp = vec_sub_vec(&cp, &(cone->c));
			det = vec_dot_vec(&cp, &(cone->v));
			if (det >= 0.0f && det <= cone->h)
				return (t[i]);
		}
		i++;
	}
	return (-1.0f);
}

static int				cone_intersect(
	void *object,
	t_ray *ray,
	float *t
)
{
	t_cone							*cone;
	float							det;
	t_cone_intersect_coefficients	coeffs;

	cone = (t_cone *)object;
	get_coefficients(&coeffs, cone, ray);
	det = coeffs.b * coeffs.b - coeffs.a * coeffs.c;
	if (det < 0.0f)
		return (RT_FALSE);
	*t = get_t(&coeffs, det, cone, ray);
	if (*t < 0.0f)
		return (RT_FALSE);
	return (RT_TRUE);
}

t_object_wrapper		new_cone(
	t_new_object_args *args_obj,
	t_new_cone_args *args_cone
)
{
	t_object_wrapper	object_wrapper;
	t_cone				*cone;

	object_wrapper.object = ft_memalloc(sizeof(t_cone));
	if (object_wrapper.object == NULL)
		handle_memalloc_err("cone");
	set_new_object(&object_wrapper, args_obj,
		&cone_intersect, NULL); // add cone normal after
	cone = (t_cone *)object_wrapper.object;
	cone->theta = args_cone->theta;
	cone->cos_2_theta = pow(cos(cone->theta), 2);
	cone->h = args_cone->h;
	cone->c = args_cone->c;
	cone->v = normalize(&(args_cone->v));
	return (object_wrapper);
}