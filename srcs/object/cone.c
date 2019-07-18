#include "rt.h"

// static t_vec4			cone_normal(
// 	void *object,
// 	t_vec4 *point
// )
// {
// 	t_cone		*cone;
// 	float		k;
// 	t_vec4		cp;
// 	t_vec4		n;

// 	cone = (t_cone *)object;
// 	cp = vec_sub_vec(point, &(cone->c));
// 	k = vec_dot_vec(&cp, &cp) / vec_dot_vec(&(cone->v), &cp);
// 	n = scalar_mul_vec(k, &(cone->v));
// 	n = vec_sub_vec(&cp, &n);
// 	return (normalize(&n));
// }

// static void				get_coefficients(
// 	t_cone_intersect_coefficients *coeffs,
// 	t_cone *cone,
// 	t_ray *ray
// )
// {
// 	float		ce_v;
// 	float		d_v;
// 	t_vec4		ce;

// 	ce = vec_sub_vec(&(ray->e), &(cone->c));
// 	ce_v = vec_dot_vec(&ce, &(cone->v));
// 	d_v = vec_dot_vec(&(ray->d), &(cone->v));
// 	coeffs->a = d_v * d_v - cone->cos_2_theta;
// 	coeffs->b = ce_v * d_v - vec_dot_vec(&(ray->d), &ce) * cone->cos_2_theta;
// 	coeffs->c = ce_v * ce_v - vec_dot_vec(&ce, &ce) * cone->cos_2_theta;
// }

// static float			get_t(
// 	t_cone_intersect_coefficients *coeffs,
// 	float det,
// 	t_cone *cone,
// 	t_ray *ray
// )
// {
// 	int			i;
// 	float		t[2];
// 	t_vec4		cp;

// 	t[0] = (-1.0f * coeffs->b - sqrtf(det)) / coeffs->a;
// 	t[1] = (-1.0f * coeffs->b + sqrtf(det)) / coeffs->a;
// 	if (coeffs->a < 0.0f)
// 		ft_swap(&(t[0]), &(t[1]), sizeof(float));
// 	i = 0;
// 	while (i < 2)
// 	{
// 		if (t[i] >= 0.0f)
// 		{
// 			cp = hit_point(ray, t[i]);
// 			cp = vec_sub_vec(&cp, &(cone->c));
// 			det = vec_dot_vec(&cp, &(cone->v));
// 			if (det >= 0.0f && det <= cone->h)
// 				return (t[i]);
// 		}
// 		i++;
// 	}
// 	return (-1.0f);
// }

// static int				cone_intersect(
// 	void *object,
// 	t_ray *ray,
// 	float *t
// )
// {
// 	t_cone							*cone;
// 	float							det;
// 	t_cone_intersect_coefficients	coeffs;

// 	cone = (t_cone *)object;
// 	get_coefficients(&coeffs, cone, ray);
// 	det = coeffs.b * coeffs.b - coeffs.a * coeffs.c;
// 	if (det < 0.0f)
// 		return (RT_FALSE);
// 	*t = get_t(&coeffs, det, cone, ray);
// 	if (*t < 0.0f)
// 		return (RT_FALSE);
// 	return (RT_TRUE);
// }

size_t		new_cone(
	t_object_commons commons,
	t_new_cone_args *args_cone,
	char *objects_buf
)
{
	t_cone			cone;

	cone.commons = commons;
	cone.theta = args_cone->theta;
	cone.cos_2_theta = powf(cosf(cone.theta), 2);
	cone.h = args_cone->h;
	cone.c = args_cone->c;
	cone.v = normalize(&(args_cone->v));
	write_object(objects_buf, (char *)&cone, sizeof(cone), RT_OBJECT_TYPE_CONE);
	return (sizeof(cone) + sizeof(int));
}