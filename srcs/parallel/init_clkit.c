/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_clkit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:01:44 by jebae             #+#    #+#             */
/*   Updated: 2019/08/01 17:05:13 by jebae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int			handle_fail(char *src)
{
	ft_memdel((void **)&src);
	return (RT_FAIL);
}

static int			create_kernels(t_clkit *clkit, char *kernel_name)
{
	if ((clkit->kernels = (cl_kernel *)ft_memalloc(sizeof(cl_kernel))) == NULL)
		exit_with_memalloc_err("kernels");
	if (clk_create_kernel(
		clkit->kernels, clkit->program, kernel_name) == CLKIT_FAIL)
		return (RT_FAIL);
	return (RT_SUCCESS);
}

int					init_clkit(
	t_clkit *clkit,
	t_global_settings *settings
)
{
	char			*src;

	src = NULL;
	if (clk_set_device(clkit, settings->parallel_mode) == CLKIT_FAIL)
		return (handle_fail(src));
	clk_get_device_info(clkit);
	if (clk_create_context(clkit) == CLKIT_FAIL)
		return (handle_fail(src));
	if (clk_create_cmd_queues(clkit) == CLKIT_FAIL)
		return (handle_fail(src));
	if (create_buffers(clkit, settings) == CLKIT_FAIL)
		return (handle_fail(src));
	src = concat_kernel_src();
	if (src == NULL)
		exit_with_memalloc_err("kernel sources");
	if (clk_create_program(&(clkit->program),\
		clkit->context, src) == CLKIT_FAIL)
		return (handle_fail(src));
	if (clk_build_program(clkit->program,\
		&(clkit->devices[0])) == CLKIT_FAIL)
		return (handle_fail(src));
	if (create_kernels(clkit, "render") == RT_FAIL)
		return (handle_fail(src));
	ft_memdel((void **)&src);
	return (RT_SUCCESS);
}
