#include "rt.h"

void	exit_with_memalloc_err(const char *msg)
{
	put_color_str(KRED, "RT : memalloc : Failed to allocate ");
	put_color_str(KRED, msg);
	ft_putchar('\n');
	exit(1);
}