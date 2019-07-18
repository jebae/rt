#include "rt_parallel.h"

static int			handle_fail(char *src)
{
	ft_memdel((void **)&src);
	return (RT_FAIL);
}

static int			create_kernels(t_clkit *clkit, char *kernel_name)
{
	if ((clkit->kernels = (cl_kernel *)ft_memalloc(sizeof(cl_kernel))) == NULL)
		exit_with_memalloc_err("kernels");
	if (clk_create_kernel(clkit->kernels, clkit->program, kernel_name) == CLKIT_FAIL)
		return (RT_FAIL);
	return (RT_SUCCESS);
}

int					init_clkit(
	t_clkit *clkit,
	char **kernel_srcs,
	size_t num_kernel_files,
	t_global_settings *settings
)
{
	char			*src;

	src = NULL;
	if (clk_set_device(clkit, CL_DEVICE_TYPE_GPU) == CLKIT_FAIL)
		return (handle_fail(src));
	clk_get_device_info(clkit);
	if (clk_create_context(clkit) == CLKIT_FAIL)
		return (handle_fail(src));
	if (clk_create_cmd_queues(clkit) == CLKIT_FAIL)
		return (handle_fail(src));
	if (create_buffers(clkit, settings) == CLKIT_FAIL)
		return (handle_fail(src));
	src = clk_concat_kernel_src(kernel_srcs, num_kernel_files);
	if (src == NULL)
		exit_with_memalloc_err("kernel sources");
	if (clk_create_program(&(clkit->program),\
		clkit->context, src) == CLKIT_FAIL)
		return (handle_fail(src));
	if (clk_build_program(clkit->program,\
		&(clkit->devices[0])) == CLKIT_FAIL)
		return (handle_fail(src));
	if (create_kernels(clkit, settings->kernel_name) == RT_FAIL)
		return (handle_fail(src));
	ft_memdel((void **)&src);
	return (RT_SUCCESS);
}
