#include "rt_test.h"

void		init_mlx(
	t_test_dispatcher *dispatcher,
	float width,
	float height
)
{
	dispatcher->p_mlx = mlx_init();
	dispatcher->p_win = mlx_new_window(
		dispatcher->p_mlx, (int)width, (int)height, "test window");
	mlx_key_hook(dispatcher->p_win, &key_press, dispatcher);
}