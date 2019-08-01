/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:02:19 by jebae             #+#    #+#             */
/*   Updated: 2019/08/01 17:02:20 by jebae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	exit_with_memalloc_err(const char *msg)
{
	put_color_str(KRED, "RT : memalloc : Failed to allocate ");
	put_color_str(KRED, msg);
	ft_putchar('\n');
	exit(1);
}
