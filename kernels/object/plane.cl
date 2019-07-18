int					plane_intersect(
	__global char *objects_buf,
	t_ray *ray,
	float *t
)
{
	t_plane		plane;
	float		det;
	t_vec4		v;

	plane = *(__global t_plane *)objects_buf;
	det = vec_dot_vec(&(ray->d), &(plane.n));
	if (ABS(det) <= FLOAT_APPROX_0)
		return (RT_FALSE);
	v = vec_sub_vec(&(plane.p), &(ray->e));
	*t = vec_dot_vec(&v, &(plane.n)) / det;
	if (*t < 0.0f)
		return (RT_FALSE);
	return (RT_TRUE);
}

t_vec4				plane_normal(
	__global char *objects_buf,
	t_vec4 *point
)
{
	t_plane		plane;

	plane = *(__global t_plane *)objects_buf;
	return (plane.n);
}