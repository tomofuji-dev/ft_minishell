/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:51:23 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/31 16:43:10 by Yoshihiro K      ###   ########.fr       */
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
# define CHRS_DELIM			" <>|"
# define CHRS_QUOTE			"$\"'"

# define CHR_DIR			'/'
# define CHR_HOME			'~'
# define CHR_SPACE			' '
# define CHR_NL				'\n'
# define CHR_SEP			':'
# define CHR_EQUAL			'='
# define CHR_SNAKE			'_'
# define CHR_STATUS			'?'

# define STR_EMPTY			""
# define STR_DIR			"/"
# define STR_OLDPWD			"-"
# define STR_QUOTE			"\""
# define STR_EXPAND			"$"

# define CMD_CD				"cd"
# define CMD_ECHO			"echo"
# define CMD_ENV			"env"
# define CMD_EXIT			"exit"
# define CMD_EXPORT			"export"
# define CMD_PWD			"pwd"
# define CMD_UNSET			"unset"

# define OPTION_NONL		"-n"

# define ENV_HOME			"HOME"
# define ENV_PATH			"PATH"
# define ENV_PWD			"PWD"
# define ENV_OLDPWD			"OLDPWD"

# define INVALID_FILENO		-1
# define ERR_NOERR			0
# define STATUS_SUCCESS		0
# define STATUS_FAILURE		1
# define STATUS_NOT_EXEC	126
# define STATUS_NO_CMD		127
# define STATUS_BASE		128
# define STATUS_MASK		0xff

# define MSG_SIG_QUIT		"Quit: 3"
# define MSG_SYNTAX_ERR		"syntax error"
# define MSG_HEREDOC_EOF	"here-document delimited end-of-file"
# define MSG_EXIT			"exit"
# define MSG_NO_OLDPWD		"OLDPWD not set"
# define MSG_ENOENT			"No such file or directory"
# define MSG_ARG_NOTNUM		"numeric argument required"
# define MSG_ARG_MANY		"too many arguments"
# define MSG_DECLARE		"declare -x "
# define MSG_INVAL_ID		"bash: %s: `%s\" : not a valid identifier\n"
# define MSG_NO_CMD			"command not found"
# define MSG_ISDIR			"Is a directory"

# define PROMPT_MINISH		"minishell $ "
# define PROMPT_HREDOC		"> "

# define SIZE_INVALID		-1

# define FLAG_NONE			0x00
# define FLAG_STRING		0x10
# define FLAG_IN			0x20
# define FLAG_HEREDOC		0x22
# define FLAG_OUT			0x40
# define FLAG_APPEND		0x44
# define FLAG_PIPE			0x80
# define SHIFT_FLAG			4

# define LEN_QUOTE_CLOSED	2
# define LEN_QUOTE_UNCLOSED	1

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
	t_cmd	*cmd;
	bool	kill_child;
	bool	heredoc_sigint;
}	t_shell;

extern t_shell	g_shell;

void	init_global(char *envp[]);
void	ms_sigset_rl(void);
void	ms_sigset_rl_heredoc(void);
void	ms_sigset_exec(void);
void	ms_sigset_noquit(void);
void	ms_sighandler_rl(int signum, siginfo_t *info, void *context);
void	ms_sighandler_rl_heredoc(int signum, siginfo_t *info, void *context);
void	ms_sighandler_exec(int signum, siginfo_t *info, void *context);

t_token	*ms_lexer(char *line);

void	ms_lexer_gettoken(t_token *token, char *line);

size_t	ms_lexer_tokenlen(char *line);
size_t	ms_lexer_tokenlen_quoted(char *line);
size_t	ms_lexer_tokenlen_plain(char *line);

char	*ms_lexer_string(char *line);

t_cmd	*ms_parser(t_token *token);
t_cmd	*ms_parser_cmdnew(t_token *token, size_t *idx);
char	**ms_parser_cmdnew_arg(t_token *token, size_t i_token);
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

void	ms_lexer_string_lstadd_back_substr(t_list **head, char *line, \
			size_t pos, size_t len);
char	*ms_lexer_string_lst_strjoin(t_list *head);

char	*ms_getpath_cmd(char *name);
char	*ms_getpath_relative(char *name);
char	*ms_getpath_envpath(char *name);
char	*ms_getpath_join(char *dirpath, char *name);
void	ms_setpath_home(char *path, char *arg);
void	ms_setpath_absolute(char *path, char *arg);
void	ms_setpath_relative(char *path, char *arg);

void	ms_exec(t_cmd *cmd);
void	ms_exec_in_child_process(t_cmd *cmd);
void	ms_exec_a_builtin(t_cmd *cmd, int (*builtin)(char *arg[]));

void	ms_fd_close(int fd[2]);
void	ms_fd_copy(int dest[2], int src[2]);
int		ms_fd_last_fd(t_fd *fd_lst);
void	ms_fd_close_all_cmd(t_cmd *cmd);
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
void	*ms_lstclear_return_null(t_list **head);
char	**ms_map_lst2map(t_list *lst);
void	*ms_map_clear(char **map, size_t size);
size_t	ms_map_size(char **map);

bool	ms_strisdigit(char *str);
void	*free_and_return(void *malloc_obj);
void	*print_err_set_status_return_null(char *str, int status);
void	*ms_clear_cmd_and_return_null(t_cmd *head);
bool	ms_is_directory(char *path);

#endif
