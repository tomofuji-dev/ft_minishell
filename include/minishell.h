/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:51:23 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/27 17:45:03 by t.fuji           ###   ########.fr       */
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
# include <limits.h>
# include <errno.h>
# include <string.h>
# include "libft.h"

//# define CHRS_DELIM		" <>|;&()" for bonus+
# define CHRS_DELIM		" <>|"
# define CHRS_QUOTE		"\"'"
# define ENV_HOME		"HOME"
# define ENV_PWD		"PWD"
# define ENV_OLDPWD		"OLDPWD"
# define MSG_EXIT		"exit"
# define STR_DIR		"/"
# define CHR_DIR		'/'
# define CHR_HOME		'~'
# define SIZE_INVALID	-1
# define FLAG_STRING	0x10
# define FLAG_IN		0x20
# define FLAG_HEREDOC	0x22
# define FLAG_OUT		0x40
# define FLAG_APPEND	0x44
# define FLAG_PIPE		0x80

typedef struct sigaction	t_sa;

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
}	t_cmd;

typedef struct s_shell {
	t_list	*environ;
	int		status;
}	t_shell;

extern t_shell	g_shell;

void	init_global(char *envp[]);
void	ms_sigset_rl(void);
void	ms_sigset_rl_heredoc(void);
void	ms_sigset_exec(void);
void	ms_sighandler_rl(int signum, siginfo_t *info, void *context);
void	ms_sighandler_rl_heredoc(int signum, siginfo_t *info, void *context);
void	ms_sighandler_exec(int signum, siginfo_t *info, void *context);

t_token	*ms_lexer(char *line);
size_t	ms_lexer_tokensize(char *line);

void	ms_lexer_gettoken(t_token *token, char *line);
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
char	*ms_getenv_line(char *env_key);
char	*ms_getenv_val(char *env_key);
bool	ms_is_same_envkey(char *dest, char *src);
bool	ms_is_validenv(char *env_candidate);

void	*ms_lstclear_return_null(t_list **head);
void	ms_lstadd_back_substr(t_list **head, char *line, \
								size_t pos, size_t len);
char	*ms_linkedls_to_str(t_list *head);

char	*ms_getpath_cmd(char *name);
char	*ms_getpath_relative(char *name);
char	*ms_getpath_envpath(char *name);
char	*ms_getpath_join(char *dirpath, char *name);
void	ms_setpath_home(char *path, char *arg);
void	ms_setpath_absolute(char *path, char *arg);
void	ms_setpath_relative(char *path, char *arg);

void	ms_exec_in_child_process(t_cmd *cmd);
void	ms_exec_a_builtin(t_cmd *cmd, int (*builtin)(char *arg[]));

void	ms_fd_close(int fd[2]);
void	ms_fd_copy(int dest[2], int src[2]);
int		ms_fd_last_fd(t_fd *fd_lst);
void	ms_fd_close_all_cmd(t_cmd *cmd);
void	ms_fd_close_fds(t_fd *fd);
void	ms_init_fd(int fd[2]);

int		(*ms_builtin_getfunc(char *arg))(char *argv[]);
int		ms_builtin_cd(char *argv[]);
int		ms_builtin_echo(char *argv[]);
int		ms_builtin_env(char *argv[]);
int		ms_builtin_exit(char *argv[]);
int		ms_builtin_export(char *argv[]);
void	ms_search_env_and_set(char *env_key);
int		ms_builtin_pwd(char *argv[]);
int		ms_builtin_unset(char *argv[]);

size_t	ms_strlst_count(char *str_lst[]);
void	ms_strlst_cpy(char **dest, char **src);
void	ms_strlst_free(char *argv[]);
char	**ms_lst2map(t_list *lst);

bool	ms_strisdigit(char *str);
void	*free_and_return(void *malloc_obj);
void	*print_err_set_status_return_null(char *str, int status);
void	*ms_clear_cmd_and_return_null(t_cmd *head);
bool	ms_is_directory(char *path);

#endif
