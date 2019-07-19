#include "rt.h"

// static t_vec4		triangle_normal(
// 	void *object,
// 	t_vec4 *point
// )
// {
// 	point = NULL;
// 	return (((t_triangle *)object)->n);
// }

// static int			triangle_intersect(
// 	void *object,
// 	t_ray *ray,
// 	float *t
// )
// {
// 	int				solution_found;
// 	t_triangle		*triangle;
// 	t_mat4			mat;
// 	t_vec4			v;

// 	triangle = (t_triangle *)object;
// 	ft_memcpy(mat.arr[0], &(triangle->u), sizeof(t_vec4));
// 	ft_memcpy(mat.arr[1], &(triangle->v), sizeof(t_vec4));
// 	ft_memcpy(mat.arr[2], &(ray->d), sizeof(t_vec4));
// 	mat = mat_transpose(&mat);
// 	v = vec_sub_vec(&(triangle->a), &(ray->e));
// 	v = mat3_cramer_solution(&mat, &v, &solution_found);
// 	if (solution_found == GMATH_FALSE)
// 		return (RT_FALSE);
// 	if (v.arr[0] >= 0.0f && v.arr[1] >= 0.0f &&\
// 		v.arr[0] + v.arr[1] <= 1.0f && v.arr[2] >= 0.0f)
// 	{
// 		*t = v.arr[2];
// 		return (RT_TRUE);
// 	}
// 	return (RT_FALSE);
// }

size_t		new_triangle(
	t_object_commons commons,
	t_new_triangle_args *args_triangle,
	char *objects_buf
)
{
	t_triangle			triangle;

	triangle.commons = commons;
	triangle.a = args_triangle->a;
	triangle.u = args_triangle->u;
	triangle.v = args_triangle->v;
	triangle.n = vec_cross_vec(&(triangle.u), &(triangle.v));
	triangle.n = normalize(&(triangle.n));
	write_mem_buf(objects_buf,
		(char *)&triangle, sizeof(triangle), RT_OBJECT_TYPE_TRIANGLE);
	return (sizeof(triangle) + sizeof(int));
}