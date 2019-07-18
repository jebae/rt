t_vec4		ambient(t_vec4 *i_a, t_vec4 *k_a)
{
	int			i;
	t_vec4		a;

	i = 0;
	while (i < 3)
	{
		a.arr[i] = i_a->arr[i] * k_a->arr[i];
		i++;
	}
	return (a);
}