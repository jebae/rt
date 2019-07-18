#include "rt_parallel.h"

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
	if (clk_set_kernel_arg(kernel, 3, sizeof(t_ray_grid_properties),
		&(settings->ray_grid_props)) == CLKIT_FAIL)
		return (RT_FAIL);
	if (clk_set_kernel_arg(kernel, 4, sizeof(int),
		&(settings->num_objects)) == CLKIT_FAIL)
		return (RT_FAIL);
	if (clk_set_kernel_arg(kernel, 5, sizeof(int),
		&(settings->num_lights)) == CLKIT_FAIL)
		return (RT_FAIL);
	if (clk_set_kernel_arg(kernel, 6, sizeof(t_vec4),
		&(settings->i_a)) == CLKIT_FAIL)
		return (RT_FAIL);
	if (clk_set_kernel_arg(kernel, 7, sizeof(int),
		&(settings->window_width)) == CLKIT_FAIL)
		return (RT_FAIL);
	return (RT_SUCCESS);
}