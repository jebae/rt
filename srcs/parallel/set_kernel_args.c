#include "rt_parallel.h"

int			set_kernel_args(
	cl_kernel kernel,
	cl_mem *mems,
	t_global_settings *settings
)
{
	if (clk_set_kernel_arg(
		kernel, 0, sizeof(cl_mem), &(mems[RT_CL_MEM_IMAGE])) == CLKIT_FAIL)
		return (RT_FAIL);
	if (clk_set_kernel_arg(
		kernel, 1, sizeof(int), settings->num_objects) == CLKIT_FAIL)
		return (RT_FAIL);
	if (clk_set_kernel_arg(
		kernel, 1, sizeof(cl_mem), &(mems[RT_CL_MEM_OBJECT_WRAPPERS])) == CLKIT_FAIL)
		return (RT_FAIL);
	if (clk_set_kernel_arg(
		kernel, 1, sizeof(cl_mem), &(mems[RT_CL_MEM_OBJECTS])) == CLKIT_FAIL)
		return (RT_FAIL);
	return (RT_SUCCESS);
}