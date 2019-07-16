#include "rt_parallel.h"

static size_t		get_object_size(char type)
{
	if (type == RT_OBJECT_TYPE_SPHERE)
		return (sizeof(t_sphere));
	else if (type == RT_OBJECT_TYPE_SPHERE)
		return (sizeof(t_sphere));
	else if (type == RT_OBJECT_TYPE_CONE)
		return (sizeof(t_cone));
	return (0);
}

static int			create_object_wrappers_buffer(
	cl_mem *mem,
	t_create_buffer_args *args,
	t_object_wrapper *object_wrappers,
	int num_objects
)
{
	args->flags = CL_MEM_COPY_HOST_PTR;
	args->size = sizeof(t_object_wrapper) * num_objects;
	args->host_ptr = object_wrappers;
	return (clk_create_buffer(mem, args));
}

static int			create_objects_buffer(
	cl_mem *mem,
	t_create_buffer_args *args,
	t_object_wrapper *object_wrappers,
	int num_objects
)
{
	int							i;
	size_t						size;
	char						*objects;
	char						*ptr;

	i = -1;
	size = 0;
	while (++i < num_objects)
		size += get_object_size(object_wrappers[i].type);
	if ((objects = (char *)ft_memalloc(size)) == NULL)
		exit_with_memalloc_err("objects buffer");
	ptr = objects;
	i = -1;
	while (++i < num_objects)
	{
		size = get_object_size(object_wrappers[i].type);
		ft_memcpy(ptr, object_wrappers[i].object, size);
		ptr += size;
	}
	args->flags = CL_MEM_COPY_HOST_PTR;
	args->size = sizeof(t_object_wrapper) * num_objects;
	args->host_ptr = objects;
	i = clk_create_buffer(mem, args);
	ft_memdel((void **)&objects);
	return (i);
}

static int			create_image_buffer(
	cl_mem *mem,
	t_create_buffer_args *args,
	float width,
	float height
)
{
	args->flags = CL_MEM_WRITE_ONLY;
	args->size = sizeof(int) * (int)width * (int)height;
	return (clk_create_buffer(mem, args));
}

int					create_buffers(
	t_clkit *clkit,
	t_global_settings *settings
)
{
	t_create_buffer_args		args;

	args.context = clkit->context;
	clkit->mems = (cl_mem *)ft_memalloc(sizeof(cl_mem) * RT_NUM_CL_MEMS);
	if (clkit->mems == NULL)
		exit_with_memalloc_err("cl mem objects");
	if (create_image_buffer(
		&(clkit->mems[RT_CL_MEM_IMAGE]), &args,
		settings->window_width, settings->window_height) == CLKIT_FAIL)
		return (RT_FAIL);
	if (create_object_wrappers_buffer(
		&(clkit->mems[RT_CL_MEM_OBJECT_WRAPPERS]), &args,
		settings->object_wrappers, settings->num_objects) == CLKIT_FAIL)
		return (RT_FAIL);
	if (create_objects_buffer(
		&(clkit->mems[RT_CL_MEM_OBJECTS]), &args,
		settings->object_wrappers, settings->num_objects) == CLKIT_FAIL)
	return (RT_SUCCESS);	
}