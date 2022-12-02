/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:51:23 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/02 14:19:40 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdbool.h>
# include <stdio.h>
# include "libft.h"

typedef struct s_cmd
{
	char			cmd_path[1024];
	char			**cmd_split;
	char			**envp;
	struct s_cmd	*next;
	//input_fd, output_fd, type
}	t_cmd;

bool	pp_check_argc(int argc);
bool	pp_check_argc(int argc);
t_cmd	*pp_args_to_cmdlst(int argc, char *argv[], char **envp);
bool	pp_cmd_add_back(t_cmd *cmd_lst, char *cmd_str, \
						char *envp[], char **env_split);
void	pp_clear_cmdlst(t_cmd *cmd_lst, int free_size);

#endif