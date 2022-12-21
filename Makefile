# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/16 16:52:37 by ykosaka           #+#    #+#              #
#    Updated: 2022/12/20 11:06:44 by Yoshihiro K      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ********************** Section for Macros (Variables) ********************** #
# Product file
NAME			= minishell

# Component names
LIBNAME			= libft

# Check the platform
OS				= $(shell uname)

# Enumeration of files
SRC				= ms_main.c \
				  ms_init.c \
				  ms_lexer.c \
				  ms_lexer_gettoken.c \
				  ms_lexer_string.c \
				  ms_lexer_string_env.c \
				  ms_lexer_string_lst.c \
				  ms_lexer_tokenlen.c \
				  ms_parser.c \
				  ms_parser_cmdnew.c \
				  ms_parser_cmdnew_arg.c \
				  ms_parser_cmdnew_input.c \
				  ms_parser_cmdnew_output.c \
				  ms_parser_cmdnew_fdsize.c \
				  ms_getpath.c \
				  ms_exec_builtin.c \
				  ms_exec_child.c \
				  ms_builtin.c \
				  ms_builtin_cd.c \
				  ms_builtin_echo.c \
				  ms_builtin_env.c \
				  ms_builtin_exit.c \
				  ms_builtin_pwd.c \
				  ms_utils.c

ifneq (, $(findstring test_, $(MAKECMDGOALS)))
	SRC			+= $(MAKECMDGOALS).c
endif

# Enumeration of directories
SRCDIR			= ./src
INCDIR			= ./include
LIBDIR			= $(LIBNAME)
OBJDIR			= ./obj

# Macros to replace and/or integrate
SRCS			= $(addprefix $(SRCDIR)/, $(SRC))
OBJS			= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
DEPS			= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.d)))
LIBS			= $(LIBDIR)/$(LIBNAME).a

# Aliases of commands
CC				= cc
RM				= rm

# Command options (flags)
CFLAGS			= -MMD -Wall -Wextra -Werror
DEBUGCFLAGS		= -g -ggdb -fno-omit-frame-pointer
ifneq ($(OS), Darwin)
	DEBUGCFLAGS	+= -fstack-usage		
endif
DEBUGLDFLAGS	= -fsanitize=address
INCLUDES		= -I$(INCDIR) -I$(LIBDIR)/include
RMFLAGS			= -r
LDFLAGS			= -lreadline

# Redefination when the specific target
ifeq ($(MAKECMDGOALS), debug)
	ifneq ($(OS), Darwin)
		CFLAGS	+= $(DEBUGCFLAGS)
		LDFLAGS	+= $(DEBUGLDFLAGS)
	endif
	DEF			= -D DEBUG_MODE=1
endif

ifneq (, $(findstring test_, $(MAKECMDGOALS)))
	CFLAGS		+= $(DEBUGCFLAGS)
	LDFLAGS		+= $(DEBUGLDFLAGS)
	DEF			= -D DEBUG_MODE=1
endif

# ********************* Section for targets and commands ********************* #
# Phonies
.PHONY: all clean fclean re clean_partly debug_lib debug \
		test_lexer_expansion test_lexer_gettoken test_parser test_builtin

# Mandatory targets
all: $(LIBS) $(NAME)
clean:
	$(MAKE) clean -C $(LIBDIR)
	-$(RM) $(RMFLAGS) $(OBJDIR)
fclean: clean
	$(MAKE) fclean -C $(LIBDIR)
	-$(RM) $(RMFLAGS) $(NAME)
re: fclean all

# Additional targets
debug_lib: 
	$(MAKE) debug -C $(LIBDIR)
debug: fclean debug_lib all
test_lexer_expansion:	all
test_lexer_gettoken:	all	
test_parser:			all	
test_builtin:			all	

# Recipes
$(NAME): $(OBJS)
	$(CC) $(INCLUDES) $(OBJS) $(LIBS) $(LDFLAGS) -o $(NAME)
$(LIBS):
	$(MAKE) -C $(LIBDIR)
$(OBJDIR):
	@mkdir -p $@
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(DEF) $(INCLUDES) -o $@ -c $<

# Including and ignore .dep files when they are not found
-include $(DEPS)

# ******** ******** ******** ******** **** ******** ******** ******** ******** #
