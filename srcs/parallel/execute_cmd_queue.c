#include "rt_parallel.h"

int			execute_cmd_queue(cl_command_queue cmd_queue)
{
	if (clk_flush(cmd_queue) == CLKIT_FAIL)
        return (RT_FAIL);
    if (clk_finish(cmd_queue) == CLKIT_FAIL)
        return (RT_FAIL);
	return (RT_SUCCESS);
}