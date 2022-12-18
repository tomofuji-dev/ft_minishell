/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:51:23 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/18 15:18:37 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <errno.h>
# include "libft.h"

//# define CHRS_DELIM		" <>|;&()" for bonus+
# define CHRS_DELIM		" <>|"
# define CHRS_QUOTE		"\"'"
# define SIZE_INVALID	-1
# define FLAG_STRING	0x10
# define FLAG_IN		0x20
# define FLAG_HEREDOC	0x22
# define FLAG_OUT		0x40
# define FLAG_APPEND	0x44
# define FLAG_PIPE		0x80

typedef struct s_token {
	char	*str;
	int		flag;
}	t_token;

typedef struct s_fd {
	char	*path;
	int		fd;
}	t_fd;

typedef struct s_cmd {
	char			*path;
	char			**arg;
	t_fd			*input;
	t_fd			*output;
	struct s_cmd	*next;
	struct s_cmd	*prev;
	pid_t			pid;
	int				ret_status;
	char			**envp;
}	t_cmd;

typedef struct s_shell {
	char	**envp;
}	t_shell;

// bool	pp_check_argc(int argc);
// bool	pp_check_argc(int argc);
// t_cmd	*pp_args_to_cmdlst(int argc, char *argv[], char **envp);
// bool	pp_cmd_add_back(t_cmd **cmd_lst, char *cmd_str,	char *envp[], char **env_split);
// void	pp_clear_cmdlst(t_cmd *cmd_lst, int free_size);
// void	pp_file_open(int argc, char *argv[], t_cmd *cmd);
// void	pp_file_close(t_cmd *cmd);

void	init_global(char *envp[]);

t_token	*ms_lexer(char *line);
size_t	ms_lexer_tokensize(char *line);

t_token	*ms_lexer_gettoken(char *line, size_t size);
int		ms_lexer_gettoken_classify(char *line);

size_t	ms_lexer_tokenlen(char *line);
size_t	ms_lexer_tokenlen_delim(char *line);
size_t	ms_lexer_tokenlen_quoted(char *line);
size_t	ms_lexer_tokenlen_plain(char *line);

char	*ms_lexer_string(char *line);

t_cmd	*ms_parser(t_token *token);
t_cmd	*ms_parser_cmdnew(t_token *token, size_t *idx);
char	**ms_parser_cmdnew_arg(t_token *token, size_t i_token);
size_t	ms_parser_cmdnew_arg_size(t_token *token, size_t idx);
size_t	ms_parser_cmdnew_fdsize(t_token *token, size_t idx, int flag);
t_fd	*ms_parser_cmdnew_input(t_token *token, size_t i_token);
t_fd	*ms_parser_cmdnew_output(t_token *token, size_t i_token);

bool	ms_isenvchar(int c);
char	*ms_search_env(char *env_key);
t_list	*ms_expand_envvar(char *line, size_t *pos, size_t len);
t_list	*ms_expand_envvar_dquote(char *line, size_t len);

void	*ms_lstclear_return_null(t_list **head);
void	ms_lstadd_back_substr(t_list **head, char *line, \
								size_t pos, size_t len);
char	*ms_linkedls_to_str(t_list *head);

char	*ms_getpath_cmd(char *name);
char	*ms_getpath_relative(char *name);
char	*ms_getpath_envpath(char *name);
char	*ms_getpath_join(char *dirpath, char *name);

void	*free_and_return(void *malloc_obj);

#endif
