t_ray				get_shadow_ray(
	t_trace_record *rec,
	__global char *lights_buf,
	float *dist
)
{
	t_ray				shadow_ray;
	t_light_attr		light_attr;

	shadow_ray.e = scalar_mul_vec(RT_BIAS, &(rec->normal));
	shadow_ray.e = vec_plus_vec(&(rec->point), &(shadow_ray.e));
	light_attr = get_light_attr(lights_buf, &(shadow_ray.e));
	*dist = light_attr.dist;
	shadow_ray.d = light_attr.direction;
	shadow_ray.d = scalar_mul_vec(-1.0f, &(shadow_ray.d));
	return (shadow_ray);
}

float				get_transmittance(
	t_trace_record *rec,
	__global char *lights_buf,
	__global char *objects_buf,
	int num_objects
)
{
	int					i;
	float				t;
	float				transmittance;
	float				dist;
	t_ray				shadow_ray;

	transmittance = 1.0f;
	shadow_ray = get_shadow_ray(rec, lights_buf, &dist);
	i = 0;
	while (i < num_objects)
	{
		if (intersect(objects_buf, &shadow_ray, &t) && t < dist)
			transmittance *= get_transparency(objects_buf);
		objects_buf += get_object_stride(objects_buf);
		i++;
	}
	return (transmittance);
}