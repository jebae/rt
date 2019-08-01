/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:00:54 by jebae             #+#    #+#             */
/*   Updated: 2019/08/01 17:03:47 by jebae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
	write_mem_buf(
		objects_buf, (char *)&cone, sizeof(cone), RT_OBJECT_TYPE_CONE);
	return (sizeof(cone) + sizeof(int));
}
