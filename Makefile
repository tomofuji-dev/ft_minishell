# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/16 16:52:37 by ykosaka           #+#    #+#              #
#    Updated: 2022/11/19 21:05:08 by ykosaka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ********************** Section for Macros (Variables) ********************** #
# Product file
NAME			= so_long

# Component names
LIBNAME_FT		= libftprintf
LIBNAME_MLX		= libmlx

# Check the platform
OS				= $(shell uname)

# Enumeration of files
SRC				= sl_main.c sl_mapopen.c sl_mapread.c sl_maptrim.c \
				  sl_mapchk.c sl_mapvalid.c sl_linechk.c sl_ispath.c \
				  sl_mapcount.c sl_mapclear.c sl_exit.c sl_exit_mlx.c \
				  sl_print.c \
				  sl_mlx.c sl_win.c sl_img.c sl_game.c \
				  ft_lst2map.c ft_mapseek.c ft_mapsize.c
SRC				+= debug_common.c debug_sl.c debug_sl_img.c

# Enumeration of directories
SRCDIR			= ./src
INCDIR			= ./include
LIBDIR			= ./lib
LIBDIR_FT		= $(LIBDIR)/libft
ifeq ($(OS), Darwin)
	LIBDIR_MLX	= $(LIBDIR)/minilibx_mms_20200219
else
	LIBDIR_MLX	= $(LIBDIR)/minilibx-linux
endif
OBJDIR			= ./obj

# Macros to replace and/or integrate
SRCS			= $(addprefix $(SRCDIR)/, $(SRC))
OBJS			= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
DEPS			= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.d)))
LIB_FT			= $(LIBDIR_FT)/$(LIBNAME_FT).a
ifeq ($(OS), Darwin)
	LIB_MLX		= $(LIBNAME_MLX).dylib
	LIBS		= $(LIBDIR_MLX)/$(LIB_MLX) $(LIB_FT)
else
	LIB_MLX		= $(LIBDIR_MLX)/$(LIBNAME_MLX).a
	LIBS		= $(LIB_MLX) $(LIB_FT)
endif

# Aliases of commands
CC				= cc
RM				= rm

# Command options (flags)
CFLAGS			= -MMD -Wall -Wextra -Werror
DEBUGCFLAGS		= -g -ggdb -fstack-usage -fno-omit-frame-pointer
DEBUGLDFLAGS	= -fsanitize=address
INCLUDES		= -I$(INCDIR) -I$(LIBDIR_MLX) -I$(LIBDIR_FT)/include
ifeq ($(OS), Darwin)
	LDFLAGS		= -L/usr/lib -L$(LIBDIR_MLX)
else
	LDFLAGS		= -L/usr/lib -L$(LIBDIR_MLX)/obj
	LIBS		+= -lXext -lX11
endif
RMFLAGS			= -r

# Redefination when the specific target
ifeq ($(MAKECMDGOALS), debug)
	ifneq ($(OS), Darwin)
		CFLAGS	+= $(DEBUGCFLAGS)
		LDFLAGS	+= $(DEBUGLDFLAGS)
	endif
	DEF		= -D DEBUG_MODE=1
endif

# ********************* Section for targets and commands ********************* #
# Phonies
.PHONY: all clean fclean re clean_partly debug_lib debug

# Mandatory targets
all: $(LIBS) $(NAME)
clean:
	$(MAKE) clean -C $(LIBDIR_FT)
	$(MAKE) clean -C $(LIBDIR_MLX)
	-$(RM) $(RMFLAGS) $(OBJDIR)
fclean: clean
	$(MAKE) fclean -C $(LIBDIR_FT)
	$(MAKE) clean -C $(LIBDIR_MLX)
	-$(RM) $(RMFLAGS) $(NAME)
ifeq ($(OS), Darwin)
	-$(RM) $(LIB_MLX)
endif
re: fclean all

# Additional targets
clean_partly:
	$(MAKE) clean -C $(LIBDIR_FT)
	-$(RM) $(RMFLAGS) $(OBJDIR)
debug_lib: 
	$(MAKE) debug -C $(LIBDIR_FT)
debug: clean_partly debug_lib all

# Recipes
$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) $(INCLUDES) $(OBJS) $(LIBS) -o $(NAME)
$(LIBS):
	$(MAKE) -C $(LIBDIR_FT)
	$(MAKE) -C $(LIBDIR_MLX)
ifeq ($(OS), Darwin)
	cp -p $(LIBDIR_MLX)/$(LIB_MLX) ./
endif
$(OBJDIR):
	@mkdir -p $@
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(DEF) $(INCLUDES) -o $@ -c $<

# Including and ignore .dep files when they are not found
-include $(DEPS)

# ******** ******** ******** ******** **** ******** ******** ******** ******** #
