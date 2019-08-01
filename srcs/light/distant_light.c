/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distant_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:00:44 by jebae             #+#    #+#             */
/*   Updated: 2019/08/01 17:03:13 by jebae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

size_t		new_distant_light(
	t_light_commons commons,
	t_new_distant_light_args *args_light,
	char *lights_buf
)
{
	t_distant_light		light;

	light.commons = commons;
	light.d = args_light->d;
	light.d = normalize(&(light.d));
	write_mem_buf(
		lights_buf, (char *)&light, sizeof(light), RT_LIGHT_TYPE_DISTANT);
	return (sizeof(light) + sizeof(int));
}
