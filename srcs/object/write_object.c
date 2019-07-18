#include "rt.h"

void		write_object(
	char *objects_buf,
	char *object,
	size_t size,
	int type
)
{
	ft_memcpy(objects_buf, &type, sizeof(type));
	objects_buf += sizeof(type);
	ft_memcpy(objects_buf, object, size);
}