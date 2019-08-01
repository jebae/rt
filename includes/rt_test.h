/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_test.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:07:07 by jebae             #+#    #+#             */
/*   Updated: 2019/08/01 17:10:00 by jebae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_TEST_H
# define RT_TEST_H

# include "rt.h"
# include "draw.h"
# include <mlx.h>
# include <stdio.h>

# define KEY_ESC	53

typedef struct		s_test_dispatcher
{
	void				*p_mlx;
	void				*p_win;
	t_marker			marker;
}					t_test_dispatcher;

/*
** utils - mlx
*/
void				init_mlx(
	t_test_dispatcher *dispatcher,
	float width,
	float height
);
int					key_press(int keycode, void *param);
void				key_esc(void *param);

/*
** utils - marker
*/
void				init_marker(
	t_marker *marker,
	void *p_mlx,
	void *p_win,
	t_global_settings *settings
);

char				*get_img_buffer(void *p_img, int width);

/*
** tests
*/
void				test_ray_direction(void);
void				test_cl_intersect(int parallel_mode);
void				test_cl_color(int parallel_mode);
void				test_render_scene1(int parallel_mode);

#endif
