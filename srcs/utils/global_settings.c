#include "rt.h"

void		clear_global_settings(t_global_settings *settings)
{
	ft_memdel((void **)&(settings->objects_buf));
	ft_memdel((void **)&(settings->lights_buf));
}