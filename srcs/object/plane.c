/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:01:04 by jebae             #+#    #+#             */
/*   Updated: 2019/08/01 17:04:02 by jebae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

size_t		new_plane(
	t_object_commons commons,
	t_new_plane_args *args_plane,
	char *objects_buf
)
{
	t_plane				plane;

	plane.commons = commons;
	plane.p = args_plane->p;
	plane.n = normalize(&(args_plane->n));
	write_mem_buf(
		objects_buf, (char *)&plane, sizeof(plane), RT_OBJECT_TYPE_PLANE);
	return (sizeof(plane) + sizeof(int));
}
