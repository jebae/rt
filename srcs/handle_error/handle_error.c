#include "rt.h"

int		rt_print_err(const char *msg)
{
	put_color_str(KRED, msg);
	return (RT_FAIL);
}

int		rt_print_memalloc_err(const char *target)
{
	rt_print_err("RT : memalloc : Failed to allocate ");
	rt_print_err(target);
	ft_putchar('\n');
	return (RT_FAIL);
}
