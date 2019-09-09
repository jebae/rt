#include "rt.h"

void		clear_rt_settings(t_rt_settings *settings)
{
	if (settings->objects_buf != NULL)
		ft_memdel((void **)&(settings->objects_buf));
	if (settings->lights_buf != NULL)
		ft_memdel((void **)&(settings->lights_buf));
}
