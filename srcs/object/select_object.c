#include "rt.h"

char		*select_object(char *objects_buf, int index)
{
	int		i;

	i = 0;
	while (i < index)
	{
		objects_buf += get_object_stride(objects_buf);
		i++;
	}
	return (objects_buf);
}
