#include "rt_parallel.h"

int			render_scene(t_clkit *clkit, t_global_settings *settings)
{
	if (update_buffers(clkit, settings) == RT_FAIL)
		return (RT_FAIL);
	if (set_kernel_args(*(clkit->kernels), clkit->mems, settings) == RT_FAIL)
		return (RT_FAIL);
	if (enqueue_ndrange_kernel(*(clkit->cmd_queues), *(clkit->kernels),
		settings->window_width * settings->window_height) == RT_FAIL)
		return (RT_FAIL);
	if (enqueue_read_buffer(*(clkit->cmd_queues),
		clkit->mems[RT_CL_MEM_IMAGE], settings->img_buf, settings) == RT_FAIL)
		return (RT_FAIL);
	return (execute_cmd_queue(*(clkit->cmd_queues)));
}
