#include "rt_test.h"

void		init_marker(t_marker *marker, void *p_mlx, void *p_win)
{
	marker->p_mlx = p_mlx;
    marker->p_win = p_win;
    marker->mark_pixel = &mark_pixel;
}