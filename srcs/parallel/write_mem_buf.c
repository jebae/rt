/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_mem_buf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:01:56 by jebae             #+#    #+#             */
/*   Updated: 2019/08/01 17:01:57 by jebae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		write_mem_buf(
	char *buf,
	char *content,
	size_t size,
	int type
)
{
	ft_memcpy(buf, &type, sizeof(type));
	buf += sizeof(type);
	ft_memcpy(buf, content, size);
}
