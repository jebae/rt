# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jebae <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/01 17:02:27 by jebae             #+#    #+#              #
#    Updated: 2019/09/09 17:50:00 by jebae            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# utils
KRED=\033[0;31m
KGRN=\033[0;32m
KYEL=\033[0;33m
KNRM=\033[0m
COUNTER = 0

define compile_obj
	printf "$(KGRN)[rt]$(KNRM) compile $(1)\n"
	$(CC) $(CFLAGS) $(INCLUDES) -c $(1) -o $(2)
	$(eval COUNTER=$(shell echo $$(($(COUNTER) + 1))))
endef

# compiler
CC = gcc

# lib name
NAME = librt.a

# path
SRCDIR = srcs

OBJDIR = objs

INCDIR = includes

LIBFT_PATH = ../libft

GMATH_PATH = ../gmath

CLKIT_PATH = ../clkit

# compiler options
CFLAGS = -Wall -Wextra -Werror

INCLUDES = -I ./$(INCDIR)\
	-I $(LIBFT_PATH)/includes\
	-I $(GMATH_PATH)/includes\
	-I $(CLKIT_PATH)/includes\

# srcs
SRC_LIGHT = distant_light.c\
	spherical_light.c\

SRC_OBJECT = get_object_stride.c\
	select_object.c\
	cone.c\
	cylinder.c\
	sphere.c\
	plane.c\
	triangle.c\

SRC_RAY = ray_grid_properties.c\
	set_ray.c\

SRC_RT_SETTINGS = init_settings.c\
	clear_settings.c\

SRC_PARALLEL = buffer.c\
	execute_cmd_queue.c\
	release.c\
	enqueue.c\
	init_clkit.c\
	set_kernel_args.c\
	concat_kernel_src.c\
	render.c\
	write_mem_buf.c\

SRC_HANDLE_ERROR = handle_error.c\

# objs
OBJS = $(addprefix $(OBJDIR)/, $(SRC_LIGHT:.c=.o))
OBJS += $(addprefix $(OBJDIR)/, $(SRC_OBJECT:.c=.o))
OBJS += $(addprefix $(OBJDIR)/, $(SRC_RAY:.c=.o))
OBJS += $(addprefix $(OBJDIR)/, $(SRC_RT_SETTINGS:.c=.o))
OBJS += $(addprefix $(OBJDIR)/, $(SRC_PARALLEL:.c=.o))
OBJS += $(addprefix $(OBJDIR)/, $(SRC_HANDLE_ERROR:.c=.o))

# compile objs
HEADERS = $(INCDIR)/rt.h\
	$(INCDIR)/rt_func.h\
	$(INCDIR)/rt_args.h\
	$(INCDIR)/rt_parallel.h\
	$(INCDIR)/rt_struct.h\
	$(LIBFT_PATH)/includes/libft.h\
	$(GMATH_PATH)/includes/gmath.h\
	$(CLKIT_PATH)/includes/clkit.h\

$(OBJDIR)/%.o : $(SRCDIR)/light/%.c $(HEADERS)
	@$(call compile_obj,$<,$@)
$(OBJDIR)/%.o : $(SRCDIR)/object/%.c $(HEADERS)
	@$(call compile_obj,$<,$@)
$(OBJDIR)/%.o : $(SRCDIR)/ray/%.c $(HEADERS)
	@$(call compile_obj,$<,$@)
$(OBJDIR)/%.o : $(SRCDIR)/rt_settings/%.c $(HEADERS)
	@$(call compile_obj,$<,$@)
$(OBJDIR)/%.o : $(SRCDIR)/parallel/%.c $(HEADERS)
	@$(call compile_obj,$<,$@)
$(OBJDIR)/%.o : $(SRCDIR)/handle_error/%.c $(HEADERS)
	@$(call compile_obj,$<,$@)

# build
all : $(NAME)

$(NAME) : pre_build $(OBJDIR) $(OBJS) post_build
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

pre_build :
	@printf "$(KGRN)[rt] $(KYEL)build $(NAME)\n$(KNRM)"

post_build :
	@printf "$(KGRN)[rt] $(KYEL)$(COUNTER) files compiled\n$(KNRM)"

$(OBJDIR) :
	@mkdir -p $(OBJDIR)

# commands
clean :
	@rm -rf $(OBJS)

fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY : all pre_build post_build clean fclean re
