/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:02:07 by jebae             #+#    #+#             */
/*   Updated: 2019/08/01 17:02:08 by jebae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		set_ray(
	t_ray_grid_properties *props,
	t_ray *ray,
	int scalar_x,
	int scalar_y
)
{
	t_vec4		d;
	t_vec4		v;

	v = scalar_mul_vec((float)scalar_x, &(props->dx));
	d = vec_plus_vec(&(props->offset), &v);
	v = scalar_mul_vec((float)scalar_y, &(props->dy));
	d = vec_plus_vec(&d, &v);
	ray->d = normalize(&d);
	ray->e = props->e;
}
