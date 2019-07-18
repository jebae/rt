#define RT_SUCCESS						1
#define RT_FAIL							0
#define RT_TRUE							1
#define RT_FALSE						0
#define NULL							0

#define RT_OBJECT_TYPE_SPHERE			0
#define RT_OBJECT_TYPE_CONE				1
#define RT_MAX_DEPTH					5
#define RT_MAX_RECORD					32

typedef struct			s_vec4
{
	float				arr[4];
}						t_vec4;

typedef struct				s_ray_grid_properties
{
	t_vec4		e;
	t_vec4		offset;
	t_vec4		dx;
	t_vec4		dy;
}							t_ray_grid_properties;

typedef struct				s_ray
{
	int				type;
	float			ior_medium;
	t_vec4			e;
	t_vec4			d;
}							t_ray;

typedef struct				s_object_commons
{
	int			specular_alpha;
	float		reflectivity;
	float		transparency;
	float		ior;
	t_vec4		k_a;
	t_vec4		k_d;
	t_vec4		k_s;
}							t_object_commons;

typedef struct				s_sphere
{
	float				r;
	t_vec4				c;
	t_object_commons	commons;
}							t_sphere;

typedef struct 				s_cone
{
	float				theta;
	float				h;
	float				cos_2_theta;
	t_vec4				c;
	t_vec4				v;
	t_object_commons	commons;
}							t_cone;

typedef struct				s_trace_record
{
	float					coeff;
	t_vec4					point;
	t_vec4					normal;
	t_ray					ray;
	__global char			*objects_buf;
	struct s_trace_record	*prev;
}							t_trace_record;

typedef struct				s_global_settings
{
	int					num_objects;
	int					num_lights;
	__global char		*objects_buf;
}							t_global_settings;

/*
** gmath
*/
float						vec_dot_vec(t_vec4 *v1, t_vec4 *v2);
t_vec4						scalar_mul_vec(float scalar, t_vec4 *v);
t_vec4						vec_plus_vec(t_vec4 *v1, t_vec4 *v2);
t_vec4						vec_cross_vec(t_vec4 *v1, t_vec4 *v2);
float						vec_norm(t_vec4 *v);
t_vec4						normalize_vec(t_vec4 *v);
t_vec4						vec_sub_vec(t_vec4 *v1, t_vec4 *v2);

/*
** preprocess
*/
void						set_global_settings(
	t_global_settings *settings,
	__global char *objects_buf,
	int num_objects
);

/*
** ray
*/
t_ray						ray_origin(
	t_ray_grid_properties *props,
	int scalar_x,
	int scalar_y
);

t_vec4						hit_point(t_ray *ray, float t);

void						write_record(t_trace_record *rec, float t);

int							trace(
	t_ray ray,
	t_trace_record *prev_rec,
	t_trace_record *rec,
	t_global_settings *settings
);

/*
** objects
*/
size_t						get_stride(int type);

int							intersect(
	__global char *objects_buf,
	t_ray *ray,
	float *t,
	size_t *stride
);

t_vec4						get_normal(
	__global char *objects_buf,
	t_vec4 *point
);

float						get_sphere_t(float d_ce, float d_d, float det);

int							sphere_intersect(
	__global char *objects_buf,
	t_ray *ray,
	float *t
);

t_vec4						sphere_normal(
	__global char *objects_buf,
	t_vec4 *point
);

/*
** utils
*/
void						swap_float(float *f1, float *f2);
