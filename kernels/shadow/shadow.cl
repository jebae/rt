t_ray				get_shadow_ray(
	t_trace_record *rec,
	__global char *lights_buf
)
{
	t_ray				shadow_ray;

	shadow_ray.e = scalar_mul_vec(RT_BIAS, &(rec->normal));
	shadow_ray.e = vec_plus_vec(&(rec->point), &(shadow_ray.e));
	shadow_ray.d = get_light_direction(lights_buf, &(shadow_ray.e));
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
	size_t				stride;
	t_ray				shadow_ray;
	t_object_commons	commons;

	transmittance = 1.0f;
	shadow_ray = get_shadow_ray(rec, lights_buf);
	stride = 0;
	i = -1;
	while (++i < num_objects && (objects_buf += stride))
	{
		stride = get_object_stride(objects_buf);
		if (intersect(objects_buf, &shadow_ray, &t))
		{
			commons = *(__global t_object_commons *)(objects_buf + sizeof(int));
			transmittance *= commons.transparency;
		}
	}
	return (transmittance);
}