t_vec4				diffuse(float n_l, t_vec4 *i_d, t_vec4 *k_d)
{
	int			i;
	t_vec4		res;

	i = 0;
	while (i < 3)
	{
		res.arr[i] = i_d->arr[i] * k_d->arr[i] * n_l;
		i++;
	}
	return (res);
}

t_vec4				specular(
	t_vec4 *r,
	t_ray *ray,
	t_object_commons *obj_commons,
	t_light_commons *light_commons
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
		res.arr[i] = light_commons->i_s.arr[i] *
			obj_commons->k_s.arr[i] * r_v;
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
	t_vec4						r;
	t_vec4						l;
	t_vec4						shades[2];
	float						n_l;
	t_light_commons				light_commons;

	l = get_light_direction(lights_buf, &(rec->point));
	light_commons = *(__global t_light_commons *)(lights_buf + sizeof(int));
	n_l = -1.0f * vec_dot_vec(&(rec->normal), &l);
	n_l = MAX(0.0f, n_l);
	shades[0] = diffuse(n_l, &(light_commons.i_d), &(obj_commons->k_d));
	shades[0] = scalar_mul_vec((1.0f - obj_commons->reflectivity) *
		(1.0f - obj_commons->transparency), &(shades[0]));
	r = scalar_mul_vec(2.0f * n_l, &(rec->normal));
	r = vec_plus_vec(&l, &r);
	shades[1] = specular(&r, &(rec->ray), obj_commons, &light_commons);
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