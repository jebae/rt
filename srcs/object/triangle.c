/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:01:20 by jebae             #+#    #+#             */
/*   Updated: 2019/08/01 17:01:20 by jebae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

size_t		new_triangle(
	t_object_commons commons,
	t_new_triangle_args *args_triangle,
	char *objects_buf
)
{
	t_triangle			triangle;

	triangle.commons = commons;
	triangle.a = args_triangle->a;
	triangle.u = args_triangle->u;
	triangle.v = args_triangle->v;
	triangle.n = vec_cross_vec(&(triangle.u), &(triangle.v));
	triangle.n = normalize(&(triangle.n));
	write_mem_buf(objects_buf,
		(char *)&triangle, sizeof(triangle), RT_OBJECT_TYPE_TRIANGLE);
	return (sizeof(triangle) + sizeof(int));
}
