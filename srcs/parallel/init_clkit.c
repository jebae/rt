#include "rt.h"

static int			handle_fail(char *src)
{
	if (src != NULL)
		ft_memdel((void **)&src);
	return (RT_FAIL);
}

static int			create_kernels(t_clkit *clkit, char *kernel_name)
{
	if ((clkit->kernels = (cl_kernel *)ft_memalloc(sizeof(cl_kernel))) == NULL)
		return (rt_print_memalloc_err("clkit kernels"));
	if (clk_create_kernel(
		clkit->kernels, clkit->program, kernel_name) == CLKIT_FAIL)
		return (RT_FAIL);
	return (RT_SUCCESS);
}

static int			build_kernel(t_clkit *clkit)
{
	char	*src;

	src = concat_kernel_src();
	if (src == NULL)
		return (rt_print_memalloc_err("kernel src"));
	if (clk_create_program(&(clkit->program),
		clkit->context, src) == CLKIT_FAIL)
		return (handle_fail(src));
	if (clk_build_program(clkit->program,
		&(clkit->devices[0])) == CLKIT_FAIL)
		return (handle_fail(src));
	if (create_kernels(clkit, "render") == RT_FAIL)
		return (handle_fail(src));
	ft_memdel((void **)&src);
	return (RT_SUCCESS);
}

int					init_clkit(
	t_clkit *clkit,
	t_rt_settings *settings
)
{
	clk_init_clkit(clkit, RT_NUM_CL_MEMS, RT_NUM_CL_KERNELS);
	if (clk_set_device(clkit, settings->parallel_mode) == CLKIT_FAIL)
		return (handle_fail(NULL));
	clk_get_device_info(clkit);
	if (clk_create_context(clkit) == CLKIT_FAIL)
		return (handle_fail(NULL));
	if (clk_create_cmd_queues(clkit) == CLKIT_FAIL)
		return (handle_fail(NULL));
	if (create_buffers(clkit, settings) == RT_FAIL)
		return (handle_fail(NULL));
	return (build_kernel(clkit));
}
