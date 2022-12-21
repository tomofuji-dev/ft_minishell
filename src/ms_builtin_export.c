/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:39:51 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/21 12:57:39 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_builtin_export(char *argv[])
{
	char	*equal_pos;

	if (argv == NULL)
		return (false);
	if (ms_count_str(argv) != 2)
		return (false);
	equal_pos = ft_strchr(argv[1], '=');
	if (equal_pos == NULL || equal_pos == &argv[1])
		return (false);
}

size_t	ms_count_str(char *str_lst[])
{
	size_t	count;

	if (str_lst == NULL)
		return (0);
	count = 0;
	while (str_lst[i] != NULL)
		count++;
	return (count);
}

int	ms_builtin_export(char *argv[])
{
	extern char	**environ;
	char		**new_environ;
	size_t		env_size;
	size_t		i;

	if (ms_is_valid_env(argv) == false)
		return (-1);
	env_size = ms_env_size(environ);
	new_environ = malloc(sizeof(char *) * (env_size + 1 + 1));
	if (new_environ == NULL)
		exit(EXIT_FAILURE);
	ms_strlst_cpy(new_environ, )
}
