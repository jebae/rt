#include "rt.h"

void		write_mem_buf(
	char *buf,
	char *content,
	size_t size,
	int type
)
{
	ft_memcpy(buf, &type, sizeof(type));
	buf += sizeof(type);
	ft_memcpy(buf, content, size);
}
