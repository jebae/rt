#include "rt.h"

int			release(t_clkit *clkit)
{
	clk_release_all(clkit, RT_NUM_CL_KERNELS, RT_NUM_CL_MEMS);
	clk_free_all(clkit);
	return (RT_SUCCESS);
}
