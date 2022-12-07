/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:51:23 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/07 16:13:04 by Yoshihiro K      ###   ########.fr       */
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
# include "libft.h"

//# define CHRS_DELIM		" <>|;&()" for bonus+
# define CHRS_DELIM		" <>|"

typedef struct s_token {
	char	*token;
	int		tokenflag;
}	t_token;

bool	pp_check_argc(int argc);
bool	pp_check_argc(int argc);
t_cmd	*pp_args_to_cmdlst(int argc, char *argv[], char **envp);
bool	pp_cmd_add_back(t_cmd **cmd_lst, char *cmd_str, \
						char *envp[], char **env_split);
void	pp_clear_cmdlst(t_cmd *cmd_lst, int free_size);
void	pp_file_open(int argc, char *argv[], t_cmd *cmd);
void	pp_file_close(t_cmd *cmd);

#endif
