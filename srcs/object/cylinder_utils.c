#include "rt.h"

t_ray	cylinder_rotate_ray(t_cylinder *cylinder, t_ray *ray)
{
	t_ray		ray_rotated;

	ray_rotated.e = rotate(&(cylinder->q), &(ray->e), &(cylinder->q_i));
	ray_rotated.d = rotate(&(cylinder->q), &(ray->d), &(cylinder->q_i));
	return (ray_rotated);
}

t_ray	cylinder_stay_ray(t_cylinder *cylinder, t_ray *ray)
{
	cylinder = NULL;
	return (*ray);
}

t_ray	cylinder_reverse_z_ray(t_cylinder *cylinder, t_ray *ray)
{
	t_ray		ray_rotated;

	cylinder = NULL;
	ray_rotated = *ray;
	ray_rotated.e.arr[2] = -1.0f * ray->e.arr[2];
	ray_rotated.d.arr[2] = -1.0f * ray->d.arr[2];
	return (ray_rotated);
}

void	cylinder_get_coefficients(
	t_cylinder_intersect_coefficients *coeffs,
	t_cylinder *cylinder,
	t_ray *ray
)
{
	float		ce[2];

	ce[0] = ray->e.arr[0] - cylinder->c_rotated.arr[0];
	ce[1] = ray->e.arr[1] - cylinder->c_rotated.arr[1];
	coeffs->a = ray->d.arr[0] * ray->d.arr[0] + ray->d.arr[1] * ray->d.arr[1];
	coeffs->b = ray->d.arr[0] * ce[0] + ray->d.arr[1] * ce[1];
	coeffs->c = ce[0] * ce[0] + ce[1] * ce[1] - cylinder->r * cylinder->r;
}