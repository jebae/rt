/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat_kernel_src.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:01:29 by jebae             #+#    #+#             */
/*   Updated: 2019/08/01 17:01:30 by jebae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		push_parts(
	char kernel_srcs_buf[][50],
	char *files[],
	size_t num_files
)
{
	size_t		i;

	i = 0;
	while (i < num_files)
	{
		ft_strcpy(kernel_srcs_buf[i], files[i]);
		i++;
	}
}

static int		push_part_utils(char kernel_srcs_buf[][50])
{
	static char		*files[] = {
		"kernels/header.cl",
		"kernels/data_structure/trace_record_queue.cl",
		"kernels/gmath/vec4/vec4_operator.cl",
		"kernels/gmath/mat4/mat4_operator.cl",
		"kernels/preprocess/get_global_settings.cl",
		"kernels/utils/swap.cl",
	};

	push_parts(kernel_srcs_buf, files, sizeof(files) / sizeof(char *));
	return (sizeof(files) / sizeof(char *));
}

static int		push_part_light_object(char kernel_srcs_buf[][50])
{
	static char		*files[] = {
		"kernels/light/distant_light.cl",
		"kernels/light/spherical_light.cl",
		"kernels/light/get_light_attr.cl",
		"kernels/light/get_light_stride.cl",
		"kernels/object/cone.cl",
		"kernels/object/get_normal.cl",
		"kernels/object/get_object_stride.cl",
		"kernels/object/get_object_commons.cl",
		"kernels/object/intersect.cl",
		"kernels/object/plane.cl",
		"kernels/object/sphere.cl",
		"kernels/object/triangle.cl",
		"kernels/object/cylinder.cl",
	};

	push_parts(kernel_srcs_buf, files, sizeof(files) / sizeof(char *));
	return (sizeof(files) / sizeof(char *));
}

static int		push_part_ray_shade(char kernel_srcs_buf[][50])
{
	static char		*files[] = {
		"kernels/render.cl",
		"kernels/ray/hit_point.cl",
		"kernels/ray/ray_origin.cl",
		"kernels/ray/trace.cl",
		"kernels/shade/ambient.cl",
		"kernels/shade/color.cl",
		"kernels/shade/diffuse_specular.cl",
		"kernels/shade/ray_color.cl",
		"kernels/shade/reflection.cl",
		"kernels/shade/refraction.cl",
		"kernels/shadow/shadow.cl",
	};

	push_parts(kernel_srcs_buf, files, sizeof(files) / sizeof(char *));
	return (sizeof(files) / sizeof(char *));
}

char			*concat_kernel_src(void)
{
	int				num_files;
	char			*src;
	char			kernel_srcs_buf[30][50];
	char			*kernel_srcs[30];

	num_files = push_part_utils(kernel_srcs_buf);
	num_files += push_part_light_object(kernel_srcs_buf + num_files);
	num_files += push_part_ray_shade(kernel_srcs_buf + num_files);
	while (num_files--)
		kernel_srcs[num_files] = kernel_srcs_buf[num_files];
	src = clk_concat_kernel_src(kernel_srcs, 30);
	return (src);
}
