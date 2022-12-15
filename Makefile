# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/16 16:52:37 by ykosaka           #+#    #+#              #
#    Updated: 2022/12/15 20:56:29 by Yoshihiro K      ###   ########.fr        #
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
SRC				= src/ms_lexer.c \
				  src/ms_lexer_gettoken.c \
				  src/ms_lexer_string.c \
				  src/ms_lexer_string_env.c \
				  src/ms_lexer_string_lst.c \
				  src/ms_lexer_tokenlen.c \
				  src/ms_parser.c \
				  src/ms_parser_cmdnew.c \
				  src/ms_parser_cmdnew_arg.c \
				  src/ms_parser_cmdnew_input.c \
				  src/ms_parser_cmdnew_output.c \
				  src/ms_parser_cmdnew_fdsize.c \
				  src/ms_utils.c

ifeq ($(MAKECMDGOALS), test_lexer_expansion)
	SRC			+= test_lexer_expansion.c
endif

ifeq ($(MAKECMDGOALS), test_lexer_gettoken)
	SRC			+= test_lexer_gettoken.c
endif

ifeq ($(MAKECMDGOALS), test_parser)
	SRC			+= test_parser.c
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
DEBUGCFLAGS		= -g -ggdb -fstack-usage -fno-omit-frame-pointer
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
	DEF		= -D DEBUG_MODE=1
endif

ifeq ($(MAKECMDGOALS), test_*)
	ifneq ($(OS), Darwin)
		CFLAGS	+= $(DEBUGCFLAGS)
		LDFLAGS	+= $(DEBUGLDFLAGS)
	endif
	DEF		= -D DEBUG_MODE=1
endif

# ********************* Section for targets and commands ********************* #
# Phonies
.PHONY: all clean fclean re clean_partly debug_lib debug \
		test_lexer_expansion test_lexer_gettoken test_parser

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
