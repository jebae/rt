t_vec4				diffuse(float n_l, t_vec4 *intensity, t_vec4 *color)
{
	int			i;
	t_vec4		res;

	i = 0;
	while (i < 3)
	{
		res.arr[i] = intensity->arr[i] * color->arr[i] * n_l;
		i++;
	}
	return (res);
}

t_vec4				specular(
	t_vec4 *r,
	t_ray *ray,
	t_object_commons *obj_commons,
	t_vec4 *intensity
)
{
	int			i;
	float		r_v;
	t_vec4		res;

	r_v = -1.0f * vec_dot_vec(r, &(ray->d));
	r_v = MAX(0.0f, r_v);
	r_v = pow(r_v, obj_commons->specular_alpha);
	i = 0;
	while (i < 3)
	{
		res.arr[i] = intensity->arr[i] *
			obj_commons->color.arr[i] * r_v;
		i++;
	}
	return (res);
}

t_vec4				diffuse_specular(
	t_trace_record *rec,
	t_object_commons *obj_commons,
	__global char *lights_buf
)
{
	t_vec4				r;
	t_vec4				shades[2];
	t_light_attr		light_attr;
	float				n_l;

	light_attr = get_light_attr(lights_buf, &(rec->point));
	n_l = -1.0f * vec_dot_vec(&(rec->normal), &(light_attr.direction));
	n_l = MAX(0.0f, n_l);
	shades[0] = diffuse(n_l, &(light_attr.intensity), &(obj_commons->color));
	shades[0] = scalar_mul_vec((1.0f - obj_commons->reflectivity) *
		(1.0f - obj_commons->transparency), &(shades[0]));
	r = scalar_mul_vec(2.0f * n_l, &(rec->normal));
	r = vec_plus_vec(&(light_attr.direction), &r);
	shades[1] = specular(&r, &(rec->ray), obj_commons, &(light_attr.intensity));
	shades[0] = vec_plus_vec(&(shades[0]), &(shades[1]));
	return (shades[0]);
}

t_vec4			diffuse_specular_per_light(
	t_trace_record *rec,
	t_object_commons *obj_commons,
	t_global_settings *settings
)
{
	int				i;
	size_t			stride;
	t_vec4			shade;
	t_vec4			temp;
	__global char 	*lights_ptr;

	lights_ptr = settings->lights_buf;
	i = -1;
	while (++i < 3)
		shade.arr[i] = 0.0f;
	shade.arr[3] = 1.0f;
	stride = 0;
	i = -1;
	while (++i < settings->num_lights && (lights_ptr += stride))
	{
		stride = get_light_stride(lights_ptr);
		temp = diffuse_specular(rec, obj_commons, lights_ptr);
		temp = scalar_mul_vec(
			get_transmittance(rec, lights_ptr, settings->objects_buf, settings->num_objects),
			&temp);
		shade = vec_plus_vec(&temp, &shade);
	}
	return (shade);
}
