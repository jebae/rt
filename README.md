# rt

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/36e53854de4d48769f3f1e70709e6e4c)](https://www.codacy.com/manual/jebae/rt?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=jebae/rt&amp;utm_campaign=Badge_Grade)

C library **rt** is part of [rt_player](https://github.com/jebae/rt_player). This library role as shader.

:warning: **Using GPU not working with macOS >= 10.14**

<br><br>

## Requirements

This library is using [libft](https://github.com/jebae/libft), [gmath](https://github.com/jebae/gmath) and [clkit](https://github.com/jebae/clkit).

```
# download libft
git clone https://github.com/jebae/libft.git

# download gmath
git clone https://github.com/jebae/gmath.git

# download clkit
git clone https://github.com/jebae/clkit.git

# directory structure
root/
  libft/
  gmath/
  clkit/
  rt/
```

instead of put required libraries in same path with rt, you can modify [Makefile](./Makefile) macro written below.

```
LIBFT_PATH = ../libft

GMATH_PATH = ../gmath

CLKIT_PATH = ../clkit
```

<br><br>

## Installation

```
make
```

<br><br>

## Features

### object
- Sphere
- Cone
- Cylinder
- Cone
- Plane
- Triangle

Getting intersection with ray, getting normal vector from intersection point functions are coded with **OpenCL C**.

<br>

### light

- Distant light
- Spherical light

<br>

### shade

- Ambient
- Diffuse
- Specular
- Reflection
- Refraction

Shader code follows phong model. Reflection and refraction recursion depth is **5** but can be manually changed editing [header.cl](./kernels/header.cl).

Reflection and refraction recursion codes use queue not real recursion. (GPU does not support recursion with OpenCL.)

<br><br>

### shadow

Shadow is not always black, but can be dimmed with object's transparency.