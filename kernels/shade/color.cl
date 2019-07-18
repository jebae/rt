int		rgb_to_int(t_vec4 *rgb_ratio)
{
	int			color;

	color = 0;
	color += (rgb_ratio->arr[0] > 1.0f) ? 0xFF : rgb_ratio->arr[0] * 0xFF;
	color <<= 8;
	color += (rgb_ratio->arr[1] > 1.0f) ? 0xFF : rgb_ratio->arr[1] * 0xFF;
	color <<= 8;
	color += (rgb_ratio->arr[2] > 1.0f) ? 0xFF : rgb_ratio->arr[2] * 0xFF;
	return (color);
}