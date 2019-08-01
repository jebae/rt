#include "rt.h"

int			enqueue_ndrange_kernel(
	cl_command_queue cmd_queue,
	cl_kernel kernel,
	size_t work_size
)
{
	t_enqueue_ndrange_kernel_args		args;

	args.cmd_queue = cmd_queue;
	args.kernel = kernel;
	args.work_dim = 1;
	args.global_work_size = &work_size;
	args.local_work_size = NULL;
	if (clk_enqueue_ndrange_kernel(&args) == CLKIT_FAIL)
		return (RT_FAIL);
	return (RT_SUCCESS);
}

int			enqueue_read_buffer(
	cl_command_queue cmd_queue,
	cl_mem mem,
	int *host_buf,
	t_global_settings *settings
)
{
	t_enqueue_buffer_args		args;

	args.cmd_queue = cmd_queue;
	args.mem = mem;
	args.offset = 0;
	args.size = sizeof(*host_buf) *
		settings->window_width * settings->window_height;
	args.host_buf = host_buf;
	if (clk_enqueue_read_buffer(&args) == CLKIT_FAIL)
		return (RT_FAIL);
	return (RT_SUCCESS);
}
