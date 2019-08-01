/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_settings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:02:15 by jebae             #+#    #+#             */
/*   Updated: 2019/08/01 17:02:15 by jebae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		clear_global_settings(t_global_settings *settings)
{
	ft_memdel((void **)&(settings->objects_buf));
	ft_memdel((void **)&(settings->lights_buf));
}
