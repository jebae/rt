/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:01:47 by jebae             #+#    #+#             */
/*   Updated: 2019/08/01 17:01:48 by jebae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			release(t_clkit *clkit)
{
	clk_release_all(clkit, RT_NUM_CL_KERNELS, RT_NUM_CL_MEMS);
	clk_free_all(clkit);
	return (RT_SUCCESS);
}
