#define RT_OBJECT_TYPE_SPHERE			0
#define RT_OBJECT_TYPE_CONE				1

typedef struct				s_object_wrapper
{
	char		type;
	void		*object;
	int			specular_alpha;
	float		reflectivity;
	float		transparency;
	float		ior;
	float4		k_a;
	float4		k_d;
	float4		k_s;
}							t_object_wrapper;

typedef struct				s_sphere
{
	float		r;
	float4		c;
}							t_sphere;

typedef struct 				s_cone
{
	float		theta;
	float		h;
	float		cos_2_theta;
	float4		c;
	float4		v;
}							t_cone;