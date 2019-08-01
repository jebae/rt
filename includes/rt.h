/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:06:36 by jebae             #+#    #+#             */
/*   Updated: 2019/08/01 17:06:37 by jebae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "rt_struct.h"
# include "rt_args.h"
# include "rt_func.h"
# include "rt_parallel.h"

# define RT_SUCCESS					1
# define RT_FAIL					0
# define RT_TRUE					1
# define RT_FALSE					0

# define RT_OBJECT_TYPE_SPHERE		0
# define RT_OBJECT_TYPE_CONE		1
# define RT_OBJECT_TYPE_PLANE		2
# define RT_OBJECT_TYPE_TRIANGLE	3
# define RT_OBJECT_TYPE_CYLINDER	4

# define RT_LIGHT_TYPE_DISTANT		0
# define RT_LIGHT_TYPE_SPHERICAL	1

#endif
