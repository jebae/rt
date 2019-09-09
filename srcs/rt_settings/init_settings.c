#include "rt.h"

void	init_rt_settings(
	t_rt_settings *settings,
	t_init_rt_settings_args *args
)
{
    settings->parallel_mode = args->parallel_mode;
    settings->window_width = args->width;
    settings->window_height = args->height;
    settings->i_a = args->i_a;
    settings->img_buf = args->img_buf;
}
