/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:51:23 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/12 10:07:39 by t.fuji           ###   ########.fr       */
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

typedef struct s_token {
	char	*token;
	int		tokenflag;
}	t_token;

typedef struct s_shell {
	char	**envp;
}	t_shell;

// bool	pp_check_argc(int argc);
// bool	pp_check_argc(int argc);
// t_cmd	*pp_args_to_cmdlst(int argc, char *argv[], char **envp);
// bool	pp_cmd_add_back(t_cmd **cmd_lst, char *cmd_str, \
// 						char *envp[], char **env_split);
// void	pp_clear_cmdlst(t_cmd *cmd_lst, int free_size);
// void	pp_file_open(int argc, char *argv[], t_cmd *cmd);
// void	pp_file_close(t_cmd *cmd);

void	init_global(char *envp[]);

size_t	ms_lexer_tokenlen(char *line);
size_t	ms_lexer_tokenlen_delim(char *line);
size_t	ms_lexer_tokenlen_quoted(char *line);
size_t	ms_lexer_tokenlen_plain(char *line);

char	*ms_lexer_string(char *line);

bool	ms_isenvchar(int c);
char	*ms_search_env(char *env_key);
t_list	*ms_expand_envvar(char *line, size_t *pos, size_t len);
t_list	*ms_expand_envvar_dquote(char *line, size_t len);

void	*ms_lstclear_return_null(t_list **head);
void	ms_lstadd_back_substr(t_list **head, char *line, \
								size_t pos, size_t len);
char	*ms_linkedls_to_str(t_list *head);

#endif
