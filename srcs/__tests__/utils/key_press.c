#include "rt_test.h"

int		key_press(int keycode, void *param)
{
	if (keycode == KEY_ESC)
		key_esc(param);
	return (1);
}