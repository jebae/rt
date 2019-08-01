/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_kernel_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:01:53 by jebae             #+#    #+#             */
/*   Updated: 2019/08/01 17:01:54 by jebae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			set_kernel_args(
	cl_kernel kernel,
	cl_mem *mems,
	t_global_settings *settings
)
{
	if (clk_set_kernel_arg(kernel, 0, sizeof(cl_mem),
		&(mems[RT_CL_MEM_IMAGE])) == CLKIT_FAIL)
		return (RT_FAIL);
	if (clk_set_kernel_arg(kernel, 1, sizeof(cl_mem),
		&(mems[RT_CL_MEM_OBJECTS])) == CLKIT_FAIL)
		return (RT_FAIL);
	if (clk_set_kernel_arg(kernel, 2, sizeof(cl_mem),
		&(mems[RT_CL_MEM_LIGHTS])) == CLKIT_FAIL)
		return (RT_FAIL);
	if (clk_set_kernel_arg(kernel, 3, sizeof(t_global_settings_args),
		settings) == CLKIT_FAIL)
		return (RT_FAIL);
	return (RT_SUCCESS);
}
