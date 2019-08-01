/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:00:57 by jebae             #+#    #+#             */
/*   Updated: 2019/08/01 17:00:58 by jebae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

size_t		new_cylinder(
	t_object_commons commons,
	t_new_cylinder_args *args_cylinder,
	char *objects_buf
)
{
	t_cylinder			cylinder;

	cylinder.commons = commons;
	cylinder.r = args_cylinder->r;
	cylinder.h = args_cylinder->h;
	cylinder.c = args_cylinder->c;
	cylinder.v = normalize(&(args_cylinder->v));
	write_mem_buf(objects_buf, (char *)&cylinder,
		sizeof(cylinder), RT_OBJECT_TYPE_CYLINDER);
	return (sizeof(cylinder) + sizeof(int));
}
