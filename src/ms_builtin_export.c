/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:39:51 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/22 11:55:29 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ms_builtin_export(char *argv[]);
int		ms_print_env_with_declare(void);
size_t	ms_count_add_env(char *argv[]);
bool	ms_is_validenv(char *env_candidate);
int		ms_set_environ(char **new_environ, size_t env_count, char **argv);

int	ms_builtin_export(char *argv[])
{
	char		**new_environ;
	size_t		add_count;
	size_t		env_count;
	int			return_status;

	if (ms_count_str(argv) == 1)
		return (ms_print_env_with_declare());
	env_count = ms_count_str(g_shell.environ);
	add_count = ms_count_add_env(argv);
	new_environ = ft_calloc(env_count + add_count + 1, sizeof(char *));
	if (new_environ == NULL)
		exit(EXIT_FAILURE);
	ms_strlst_cpy(new_environ, g_shell.environ);
	ms_strlst_free(g_shell.environ);
	g_shell.environ = new_environ;
	return_status = ms_set_environ(new_environ, env_count, argv);
	return (return_status);
}

int	ms_print_env_with_declare(void)
{
	size_t	i;
	char	*eq;
	int		return_status;

	i = 0;
	while (g_shell->environ[i] != NULL)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		eq = ft_strchr(g_shell.environ, '=');
		write(g_shell.environ, STDOUT_FILENO, eq - g_shell.environ + 1);
		ft_putchar_fd('"', STDOUT_FILENO);
		ft_putstr_fd(eq + 1, STDOUT_FILENO);
		ft_putendl_fd("\"", STDOUT_FILENO);
		i++;
	}
	return_status = 0;
	return (return_status);
}

size_t	ms_count_add_env(char *argv[])
{
	size_t	add_count;
	size_t	i;
	char	*eq;

	i = 0;
	add_count = 0;
	while (argv[i] != NULL)
	{
		if (ms_is_validenv(argv[i]))
		{
			eq = ft_strchr(argv[i], '=');
			if (eq != NULL)
			{
				*eq = '\0';
				if (ms_getenv_line(argv[i]) == NULL)
					add_count++;
				*eq = '=';
			}
		}
	}
	return (add_count);
}

bool	ms_is_validenv(char *env_candidate)
{
	if (ft_strchr(env_candidate, '=') == env_candidate)
		return (false);
	return (true);
}

int	ms_set_environ(char **new_environ, size_t env_count, char **argv)
{
	int		return_status;
	size_t	argv_ind;
	size_t	env_ind;
	char	*eq;
	char	*pos_in_env;

	return_status = 0;
	argv_ind = 0;
	env_ind = env_count;
	while (argv[argv_ind] != NULL)
	{
		if (ms_is_valid_env(argv[argv_ind]) == false)
		{
			printf("bash: export: `%s\" : not a valid identifier\n", argv[argv_ind]);
			return_status = 1;
			continue ;
		}
		else
		{
			eq = ft_strchr(argv[argv_ind], '=');
			if (eq == NULL)
				continue ;
			*eq = '\0';
			pos_in_env = ms_getenv_line(argv[argv_ind]);
			if (pos_in_env != NULL)
			{
				free(pos_in_env);
				pos_in_env = ft_strdup(argv[argv_ind]);
				if (pos_in_env == NULL)
					exit(EXIT_FAILURE);
			}
			else
			{
				g_shell.environ[env_ind] = ft_strdup(argv[argv_ind]);
				if (pos_in_env == NULL)
					exit(EXIT_FAILURE);
			}
		}
	}
}
