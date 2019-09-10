#include "rt.h"

static int			create_image_buffer(
	t_clk_mem *mem,
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
	t_clk_mem *mem,
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
	t_clk_mem *mem,
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
	t_rt_settings *settings
)
{
	t_create_buffer_args		args;

	args.context = &(clkit->context);
	clkit->mems = clk_new_mems(clkit->num_mems);
	if (clkit->mems == NULL)
		return (rt_print_memalloc_err("clkit mems"));
	if (create_image_buffer(
		&(clkit->mems[RT_CL_MEM_IMAGE]), settings->window_width,
		settings->window_height, &args) == CLKIT_FAIL)
		return (RT_FAIL);
	if (settings->objects_buf_size && create_objects_buffer(
		&(clkit->mems[RT_CL_MEM_OBJECTS]), settings->objects_buf,
		settings->objects_buf_size, &args) == CLKIT_FAIL)
		return (RT_FAIL);
	if (settings->lights_buf_size && create_lights_buffer(
		&(clkit->mems[RT_CL_MEM_LIGHTS]), settings->lights_buf,
		settings->lights_buf_size, &args) == CLKIT_FAIL)
		return (RT_FAIL);
	return (RT_SUCCESS);
}

int					update_buffers(
	t_clkit *clkit,
	t_rt_settings *settings
)
{
	t_create_buffer_args		args;

	args.context = &(clkit->context);
	if (settings->objects_buf_size && create_objects_buffer(
		&(clkit->mems[RT_CL_MEM_OBJECTS]), settings->objects_buf,
		settings->objects_buf_size, &args) == CLKIT_FAIL)
		return (RT_FAIL);
	if (settings->lights_buf_size && create_lights_buffer(
		&(clkit->mems[RT_CL_MEM_LIGHTS]), settings->lights_buf,
		settings->lights_buf_size, &args) == CLKIT_FAIL)
		return (RT_FAIL);
	return (RT_SUCCESS);
}
