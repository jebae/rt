/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_kernel_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:01:53 by jebae             #+#    #+#             */
/*   Updated: 2019/09/09 16:25:15 by jebae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			set_kernel_args(
	t_clk_kernel *kernel,
	t_clk_mem *mems,
	t_rt_settings *settings
)
{
	if (clk_set_kernel_arg(kernel, 0, sizeof(cl_mem),
		&(mems[RT_CL_MEM_IMAGE].obj)) == CLKIT_FAIL)
		return (RT_FAIL);
	if (clk_set_kernel_arg(kernel, 1, sizeof(cl_mem),
		&(mems[RT_CL_MEM_OBJECTS].obj)) == CLKIT_FAIL)
		return (RT_FAIL);
	if (clk_set_kernel_arg(kernel, 2, sizeof(cl_mem),
		&(mems[RT_CL_MEM_LIGHTS].obj)) == CLKIT_FAIL)
		return (RT_FAIL);
	if (clk_set_kernel_arg(kernel, 3, sizeof(t_rt_settings_args),
		settings) == CLKIT_FAIL)
		return (RT_FAIL);
	return (RT_SUCCESS);
}
