#include "rt_test.h"

char        *get_img_buffer(void *p_img, int width)
{
    static int      bpp = MLX_BPP;
    static int      endian = MLX_ENDIAN;

    return (mlx_get_data_addr(p_img, &bpp, &width, &endian));
}

void		init_marker(
	t_marker *marker,
	void *p_mlx,
	void *p_win,
	t_global_settings *settings
)
{
	marker->p_mlx = p_mlx;
    marker->p_win = p_win;
    marker->mark_pixel = &mark_pixel;
	marker->p_img = mlx_new_image(marker->p_mlx,
		settings->window_width, settings->window_height);
}