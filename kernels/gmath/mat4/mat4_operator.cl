void		vec_to_mat_row(t_vec4 *vec, t_mat4 *mat, int idx)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		mat->arr[idx][i] = vec->arr[i];
		i++;
	}
}

t_vec4		mat_mul_vec(t_mat4 *m, t_vec4 *v)
{
	int		r;
	int		c;
	t_vec4	res;

	r = 0;
	while (r < 4)
	{
		res.arr[r] = 0;
		c = 0;
		while (c < 4)
		{
			res.arr[r] += m->arr[r][c] * v->arr[c];
			c++;
		}
		r++;
	}
	return (res);
}

t_mat4		mat_mul_mat(t_mat4 *m1, t_mat4 *m2)
{
	int		r1;
	int		r2;
	int		c;
	t_mat4	res;

	r1 = 0;
	while (r1 < 4)
	{
		r2 = 0;
		res.arr[r1][r2] = 0;
		while (r2 < 4)
		{
			c = 0;
			while (c < 4)
			{
				res.arr[r1][r2] += m1->arr[r1][c] * m2->arr[c][r2];
				c++;
			}
			r2++;
		}
		r1++;
	}
	return (res);
}

t_mat4		mat_transpose(t_mat4 *mat)
{
	int			i;
	int			j;
	t_mat4		t;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			t.arr[j][i] = mat->arr[i][j];
			j++;
		}
		i++;
	}
	return (t);
}

float		mat3_det(t_mat4 *mat)
{
	float	res;

	res = (mat->arr[0][0] *
		(mat->arr[1][1] * mat->arr[2][2] - mat->arr[1][2] * mat->arr[2][1]) -
		mat->arr[1][0] *
		(mat->arr[0][1] * mat->arr[2][2] - mat->arr[0][2] * mat->arr[2][1]) +
		mat->arr[2][0] *
		(mat->arr[0][1] * mat->arr[1][2] - mat->arr[0][2] * mat->arr[1][1]));
	if (ABS(res) < FLOAT_APPROX_0)
		return (0.0f);
	return (res);
}

t_vec4		mat3_cramer_solution(t_mat4 *a, t_vec4 *b, int *solution_found)
{
	int			i;
	int			j;
	float		det;
	t_vec4		x;
	t_mat4		mat;

	det = mat3_det(a);
	if (det == 0.0f)
		*solution_found = RT_FALSE;
	i = 0;
	while (i < 3)
	{
		mat = *a;
		j = 0;
		while (j < 3)
		{
			mat.arr[j][i] = b->arr[j];
			j++;
		}
		x.arr[i] = mat3_det(&mat) / det;
		i++;
	}
	*solution_found = RT_TRUE;
	return (x);
}