#define NULL							0
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define ABS(N) ((N < 0) ? -(N) : (N))
#define FLOAT_APPROX_0            		1e-6f

#define RT_SUCCESS						1
#define RT_FAIL							0
#define RT_TRUE							1
#define RT_FALSE						0
#define RT_BACKGROUND_COLOR				0x000000

#define RT_RAY_TYPE_NONE				0
#define RT_RAY_TYPE_REFLECTION			1
#define RT_RAY_TYPE_REFRACTION			2

#define RT_OBJECT_TYPE_SPHERE			0
#define RT_OBJECT_TYPE_CONE				1
#define RT_OBJECT_TYPE_PLANE			2
#define RT_OBJECT_TYPE_TRIANGLE			3
#define RT_OBJECT_TYPE_CYLINDER			4

#define RT_LIGHT_TYPE_DISTANT			0
#define RT_LIGHT_TYPE_SPHERICAL			1

#define RT_MAX_DEPTH					5
#define RT_MAX_RECORD					63
#define RT_BIAS							1e-3

typedef struct			s_vec4
{
	float				arr[4];
}						t_vec4;

typedef struct			s_mat4
{
	float				arr[4][4];
}						t_mat4;

typedef struct			s_quaternion
{
	float				x;
	float				y;
	float				z;
	float				w;
}						t_quaternion;

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

typedef struct				s_light_commons
{
	t_vec4		intensity;
}							t_light_commons;

typedef struct				s_light_attr
{
	float		dist;
	t_vec4		direction;
	t_vec4		intensity;
}							t_light_attr;

typedef struct				s_distant_light
{
	t_light_commons		commons;
	t_vec4				d;
}							t_distant_light;

typedef struct				s_spherical_light
{
	t_light_commons		commons;
	t_vec4				origin;
}							t_spherical_light;

typedef struct				s_object_commons
{
	int			specular_alpha;
	float		reflectivity;
	float		transparency;
	float		ior;
	t_vec4		color;
}							t_object_commons;

typedef struct				s_sphere
{
	t_object_commons	commons;
	float				r;
	t_vec4				c;
}							t_sphere;

typedef struct 				s_cone
{
	t_object_commons	commons;
	float				theta;
	float				h;
	float				cos_2_theta;
	t_vec4				c;
	t_vec4				v;
}							t_cone;

typedef struct				s_cone_intersect_coefficients
{
	float				a;
	float				b;
	float				c;
}							t_cone_intersect_coefficients;

typedef struct				s_plane
{
	t_object_commons	commons;
	t_vec4				p;
	t_vec4				n;
}							t_plane;

typedef struct				s_triangle
{
	t_object_commons	commons;
	t_vec4				a;
	t_vec4				u;
	t_vec4				v;
	t_vec4				n;
}							t_triangle;

typedef struct 				s_cylinder
{
	t_object_commons	commons;
	float				r;
	float				h;
	t_vec4				c;
	t_vec4				v;
}							t_cylinder;

typedef struct				s_cylinder_intersect_coefficients
{
	float				a;
	float				b;
	float				c;
}							t_cylinder_intersect_coefficients;

typedef struct				s_trace_record
{
	float					coeff;
	int						depth;
	t_vec4					point;
	t_vec4					normal;
	t_ray					ray;
	__global char			*objects_buf;
	struct s_trace_record	*prev;
}							t_trace_record;

typedef struct				s_trace_record_queue
{
	int						count;
	int						front;
	int						rear;
	t_trace_record			queue[RT_MAX_RECORD];
}							t_trace_record_queue;

typedef struct				s_global_settings
{
	int					num_objects;
	int					num_lights;
	t_vec4				i_a;
	__global char		*objects_buf;
	__global char		*lights_buf;
}							t_global_settings;

typedef struct				s_global_settings_args
{
	int						window_width;
	int						window_height;
	int						num_objects;
	int						num_lights;
	int						parallel_mode;
	size_t					objects_buf_size;
	size_t					lights_buf_size;
	t_ray_grid_properties	ray_grid_props;
	t_vec4					i_a;
}							t_global_settings_args;

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
void						vec_to_mat_row(t_vec4 *vec, t_mat4 *mat, int idx);
t_vec4						mat_mul_vec(t_mat4 *m, t_vec4 *v);
t_mat4						mat_mul_mat(t_mat4 *m1, t_mat4 *m2);
t_mat4						mat_transpose(t_mat4 *mat);
float						mat3_det(t_mat4 *mat);
t_vec4						mat3_cramer_solution(
	t_mat4 *a,
	t_vec4 *b,
	int *solution_found
);

/*
** preprocess
*/
t_global_settings			get_global_settings(
	__global char *objects_buf,
	__global char *lights_buf,
	int num_objects,
	int num_lights,
	t_vec4 i_a
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
** light
*/
t_light_attr						get_light_attr(
	__global char *lights_buf,
	t_vec4 *point
);

t_light_attr						distant_light_attr(
	__global char *lights_buf,
	t_vec4 *point
);

t_light_attr						spherical_light_attr(
	__global char *lights_buf,
	t_vec4 *point
);

size_t								get_light_stride(__global char *buf);

/*
** objects
*/
size_t								get_object_stride(__global char *buf);

t_object_commons					get_object_commons(__global char *buf);

int									intersect(
	__global char *objects_buf,
	t_ray *ray,
	float *t
);

float								get_transparency(__global char *objects_buf);

float								get_object_ior(__global char *objects_buf);

t_vec4								get_normal(
	__global char *objects_buf,
	t_vec4 *point
);

float								get_sphere_t(float d_ce, float d_d, float det);

int									sphere_intersect(
	__global char *objects_buf,
	t_ray *ray,
	float *t
);

t_vec4								sphere_normal(
	__global char *objects_buf,
	t_vec4 *point
);

t_cone_intersect_coefficients		get_cone_intersect_coefficients(
	t_cone *cone,
	t_ray *ray
);

float								get_cone_t(
	t_cone_intersect_coefficients *coeffs,
	float det,
	t_cone *cone,
	t_ray *ray
);

t_vec4								cone_normal(
	__global char *objects_buf,
	t_vec4 *point
);

int									cone_intersect(
	__global char *objects_buf,
	t_ray *ray,
	float *t
);

int									triangle_intersect(
	__global char *objects_buf,
	t_ray *ray,
	float *t
);

t_vec4								triangle_normal(
	__global char *objects_buf,
	t_vec4 *point
);

int									plane_intersect(
	__global char *objects_buf,
	t_ray *ray,
	float *t
);

t_vec4								plane_normal(
	__global char *objects_buf,
	t_vec4 *point
);

t_cylinder_intersect_coefficients	get_cylinder_intersect_coefficients(
	t_cylinder *cylinder,
	t_ray *ray
);

float								get_cylinder_t(
	t_cylinder_intersect_coefficients *coeff,
	float det,
	t_cylinder *cylinder,
	t_ray *ray
);

int									cylinder_intersect(
	__global char *objects_buf,
	t_ray *ray,
	float *t
);

t_vec4								cylinder_normal(
	__global char *objects_buf,
	t_vec4 *point
);

/*
** data stucture
*/
void								init_rec_queue(t_trace_record_queue *rec_queue);
int									is_rec_queue_full(t_trace_record_queue *rec_queue);
int									is_rec_queue_empty(t_trace_record_queue *rec_queue);
void								push_rec_queue(
	t_trace_record_queue *rec_queue,
	t_trace_record rec
);
t_trace_record						*pop_rec_queue(t_trace_record_queue *rec_queue);

/*
** shade
*/
int									rgb_to_int(t_vec4 *rgb_ratio);

int									ray_trace(
	t_trace_record_queue *rec_queue,
	t_global_settings *settings
);

t_vec4								ray_color(
	t_trace_record *rec,
	t_global_settings *settings
);

t_vec4								diffuse_specular_per_light(
	t_trace_record *rec,
	t_object_commons *obj_commons,
	t_global_settings *settings
);

t_vec4								diffuse_specular(
	t_trace_record *rec,
	t_object_commons *obj_commons,
	__global char *lights_buf
);

t_vec4								diffuse(float n_l, t_vec4 *intensity, t_vec4 *color);

t_vec4								specular(
	t_vec4 *r,
	t_ray *ray,
	t_object_commons *obj_commons,
	t_vec4 *intensity
);

void								init_rgb_color(t_vec4 *rgb);

t_vec4								ambient(t_vec4 *intensity, t_vec4 *color);

t_ray								get_reflect_ray(t_trace_record *rec);

int									reflect_record(
	t_trace_record *prev,
	t_trace_record *cur,
	t_global_settings *settings
);

float								get_ior(t_trace_record *rec);

t_ray								get_refract_ray(t_trace_record *rec);

int									refract_record(
	t_trace_record *prev,
	t_trace_record *cur,
	t_global_settings *settings
);

/*
** shadow
*/
t_ray								get_shadow_ray(
	t_trace_record *rec,
	__global char *lights_buf,
	float *dist
);

float								get_transmittance(
	t_trace_record *rec,
	__global char *lights_buf,
	__global char *objects_buf,
	int num_objects
);

/*
** utils
*/
void								swap_float(float *f1, float *f2);
