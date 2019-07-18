#ifndef RT_PARALLEL_H
# define RT_PARALLEL_H

# include "clkit.h"
# include "rt.h"
# include <stdio.h> // remove after

# define RT_NUM_CL_KERNELS				1
# define RT_NUM_CL_MEMS					2
# define RT_CL_MEM_IMAGE				0
# define RT_CL_MEM_OBJECTS				1

int						create_buffers(
	t_clkit *clkit,
	t_global_settings *args
);

int						init_clkit(
	t_clkit *clkit,
	char **kernel_srcs,
	size_t num_kernel_files,
	t_global_settings *args
);

int						set_kernel_args(
	cl_kernel kernel,
	cl_mem *mems,
	t_global_settings *settings
);

int						enqueue_ndrange_kernel(
	cl_command_queue cmd_queue,
	cl_kernel kernel,
	size_t work_size
);

int						enqueue_read_buffer(
	cl_command_queue cmd_queue,
	cl_mem mem,
	int *host_buf,
	t_global_settings *settings
);

int						execute_cmd_queue(cl_command_queue cmd_queue);

int						release(t_clkit *clkit);

#endif