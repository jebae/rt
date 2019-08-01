/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:01:35 by jebae             #+#    #+#             */
/*   Updated: 2019/08/01 17:01:36 by jebae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int			create_image_buffer(
	cl_mem *mem,
	int width,
	int height,
	t_create_buffer_args *args
)
{
	args->flags = CL_MEM_WRITE_ONLY;
	args->size = sizeof(int) * width * height;
	args->host_ptr = NULL;
	return (clk_create_buffer(mem, args));
}

static int			create_objects_buffer(
	cl_mem *mem,
	char *objects_buf,
	size_t size,
	t_create_buffer_args *args
)
{
	args->flags = CL_MEM_COPY_HOST_PTR;
	args->size = size;
	args->host_ptr = objects_buf;
	return (clk_create_buffer(mem, args));
}

static int			create_lights_buffer(
	cl_mem *mem,
	char *lights_buf,
	size_t size,
	t_create_buffer_args *args
)
{
	args->flags = CL_MEM_COPY_HOST_PTR;
	args->size = size;
	args->host_ptr = lights_buf;
	return (clk_create_buffer(mem, args));
}

int					create_buffers(
	t_clkit *clkit,
	t_global_settings *settings
)
{
	t_create_buffer_args		args;

	args.context = clkit->context;
	clkit->mems = (cl_mem *)ft_memalloc(sizeof(cl_mem) * RT_NUM_CL_MEMS);
	if (clkit->mems == NULL)
		exit_with_memalloc_err("cl mem objects");
	if (create_image_buffer(
		&(clkit->mems[RT_CL_MEM_IMAGE]), settings->window_width,
		settings->window_height, &args) == CLKIT_FAIL)
		return (RT_FAIL);
	if (create_objects_buffer(
		&(clkit->mems[RT_CL_MEM_OBJECTS]), settings->objects_buf,
		settings->objects_buf_size, &args) == CLKIT_FAIL)
		return (RT_FAIL);
	if (create_lights_buffer(
		&(clkit->mems[RT_CL_MEM_LIGHTS]), settings->lights_buf,
		settings->lights_buf_size, &args) == CLKIT_FAIL)
		return (RT_FAIL);
	return (RT_SUCCESS);
}

int					update_buffers(
	t_clkit *clkit,
	t_global_settings *settings
)
{
	t_create_buffer_args		args;

	args.context = clkit->context;
	if (create_objects_buffer(
		&(clkit->mems[RT_CL_MEM_OBJECTS]), settings->objects_buf,
		settings->objects_buf_size, &args) == CLKIT_FAIL)
		return (RT_FAIL);
	if (create_lights_buffer(
		&(clkit->mems[RT_CL_MEM_LIGHTS]), settings->lights_buf,
		settings->lights_buf_size, &args) == CLKIT_FAIL)
		return (RT_FAIL);
	return (RT_SUCCESS);
}
