t_vec4			triangle_normal(
	__global char *objects_buf,
	t_vec4 *point
)
{
	t_triangle		triangle;

	triangle = *(__global t_triangle *)objects_buf;
	return (triangle.n);
}

int				triangle_intersect(
	__global char *objects_buf,
	t_ray *ray,
	float *t
)
{
	int				solution_found;
	t_triangle		triangle;
	t_mat4			mat;
	t_vec4			v;

	triangle = *(__global t_triangle *)objects_buf;
	v = scalar_mul_vec(-1.0f, &(triangle.u));
	vec_to_mat_row(&v, &mat, 0);
	v = scalar_mul_vec(-1.0f, &(triangle.v));
	vec_to_mat_row(&v, &mat, 1);
	vec_to_mat_row(&(ray->d), &mat, 2);
	mat = mat_transpose(&mat);
	v = vec_sub_vec(&(triangle.a), &(ray->e));
	v = mat3_cramer_solution(&mat, &v, &solution_found);
	if (solution_found == RT_FALSE)
		return (RT_FALSE);
	if (v.arr[0] >= 0.0f && v.arr[1] >= 0.0f &&
		v.arr[0] + v.arr[1] <= 1.0f && v.arr[2] >= 0.0f)
	{
		*t = v.arr[2];
		return (RT_TRUE);
	}
	return (RT_FALSE);
}