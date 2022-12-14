/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:39:51 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/31 15:24:32 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ms_builtin_export(char *argv[]);
static int		ms_print_env_with_declare(void);
static int		ms_set_environ(char **argv);
void			ms_search_env_and_set(char *env_key);
static t_list	*ms_lstnew_env(char *env_key);

int	ms_builtin_export(char *argv[])
{
	int	return_status;

	if (argv[1] == NULL)
		return (ms_print_env_with_declare());
	return_status = ms_set_environ(&argv[1]);
	return (return_status);
}

static int	ms_print_env_with_declare(void)
{
	t_list	*cur;
	char	*eq;

	cur = g_shell.environ;
	while (cur != NULL)
	{
		ft_putstr_fd(MSG_DECLARE, STDOUT_FILENO);
		eq = ft_strchr(cur->content, CHR_EQUAL);
		write(STDOUT_FILENO, cur->content, eq - (char *)cur->content + 1);
		ft_putstr_fd(STR_QUOTE, STDOUT_FILENO);
		ft_putstr_fd(eq + 1, STDOUT_FILENO);
		ft_putendl_fd(STR_QUOTE, STDOUT_FILENO);
		cur = cur->next;
	}
	return (STATUS_SUCCESS);
}

int	ms_set_environ(char **argv)
{
	int		return_status;
	size_t	i;
	char	*eq;

	return_status = STATUS_SUCCESS;
	i = 0;
	while (argv[i] != NULL)
	{
		eq = ft_strchr(argv[i], CHR_EQUAL);
		if (eq == NULL)
		{
			i++;
			continue ;
		}
		*eq = '\0';
		if (ms_is_validenv(argv[i]) == false)
		{
			*eq = CHR_EQUAL;
			printf(MSG_INVAL_ID, CMD_EXPORT, argv[i++]);
			return_status = STATUS_FAILURE;
		}
		else
			ms_search_env_and_set(argv[i++]);
	}
	return (return_status);
}

void	ms_search_env_and_set(char *env_key)
{
	t_list	*cur;
	t_list	*prev;
	t_list	*new;

	cur = g_shell.environ;
	prev = NULL;
	while (cur != NULL)
	{
		if (ms_is_same_envkey(cur->content, env_key))
		{
			free(cur->content);
			env_key[ft_strlen(env_key)] = CHR_EQUAL;
			cur->content = ft_strdup(env_key);
			if (cur->content == NULL)
				exit(EXIT_FAILURE);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
	new = ms_lstnew_env(env_key);
	if (prev == NULL)
		g_shell.environ = new;
	else
		prev->next = new;
}

t_list	*ms_lstnew_env(char *env_key)
{
	t_list	*new;

	env_key[ft_strlen(env_key)] = CHR_EQUAL;
	new = ft_lstnew(ft_strdup(env_key));
	if (new == NULL || new->content == NULL)
		exit(EXIT_FAILURE);
	return (new);
}
