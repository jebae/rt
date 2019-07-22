t_vec4		ambient(t_vec4 *intensity, t_vec4 *color)
{
	int			i;
	t_vec4		a;

	i = 0;
	while (i < 3)
	{
		a.arr[i] = intensity->arr[i] * color->arr[i];
		i++;
	}
	return (a);
}