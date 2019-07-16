#ifndef RT_TEST_H
# define RT_TEST_H

# include "rt.h"
// # include "rt_parallel.h"
# include "draw.h"
# include <mlx.h>
# include <stdio.h>

# define KEY_ESC	53

typedef struct		s_test_dispatcher
{
	void		*p_mlx;
	void		*p_win;
	t_marker	marker;
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
void				init_marker(t_marker *marker, void *p_mlx, void *p_win);

/*
** tests
*/
void				test_ray_direction(void);
void				test_sphere_intersect(void);
void				test_triangle_intersect(void);
void				test_plane_intersect(void);
void				test_disk_intersect(void);
void				test_cone_intersect(void);
void				test_cylinder_intersect(void);
void				test_color(void);
void				test_trace(void);
void				test_reflection(void);
void				test_refraction(void);

#endif