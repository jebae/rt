/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:01:07 by jebae             #+#    #+#             */
/*   Updated: 2019/08/01 17:01:08 by jebae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char		*select_object(char *objects_buf, int index)
{
	int		i;

	i = 0;
	while (i < index)
	{
		objects_buf += get_object_stride(objects_buf);
		i++;
	}
	return (objects_buf);
}
