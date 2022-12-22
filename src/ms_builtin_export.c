/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:39:51 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/22 16:16:44 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ms_builtin_export(char *argv[]);
int		ms_print_env_with_declare(void);
bool	ms_is_validenv(char *env_candidate);
int		ms_set_environ(char **argv);
void	ms_search_env_and_set(char *env_key);
t_list	*ms_lstnew_env(char *env_key);

int	ms_builtin_export(char *argv[])
{
	int			return_status;

	if (argv[1] == NULL)
		return (ms_print_env_with_declare());
	return_status = ms_set_environ(argv);
	return (return_status);
}

int	ms_print_env_with_declare(void)
{
	t_list	*cur;
	size_t	i;
	char	*eq;
	int		return_status;

	i = 0;
	cur = g_shell->environ;
	while (cur != NULL)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		eq = ft_strchr(cur->content, '=');
		write(cur->content, STDOUT_FILENO, eq - cur->content + 1);
		ft_putchar_fd('"', STDOUT_FILENO);
		ft_putstr_fd(eq + 1, STDOUT_FILENO);
		ft_putendl_fd("\"", STDOUT_FILENO);
		cur = cur->next;
	}
	return_status = 0;
	return (return_status);
}

int	ms_set_environ(char **argv)
{
	int		return_status;
	size_t	i;
	char	*eq;

	return_status = 0;
	i = 0;
	while (argv[i] != NULL)
	{
		if (ms_is_valid_env(argv[i]) == false)
		{
			printf("bash: export: `%s\" : not a valid identifier\n", argv[i]);
			return_status = 1;
			continue ;
		}
		else
		{
			eq = ft_strchr(argv[i], '=');
			if (eq == NULL)
				continue ;
			*eq = '\0';
			ms_search_env_and_set(argv[i]);
		}
		i++;
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
		if (ms_is_same_envkey(cur->content, env_key)
		{
			free(cur->content);
			env_key[ft_strlen(env_key)] = '=';
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

	env_key[ft_strlen(env_key)] = '=';
	new = ft_lstnew(ft_strdup(env_key));
	if (new == NULL || new->content == NULL)
		exit(EXIT_FAILURE);
	return (new);
}
