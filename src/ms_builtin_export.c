/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:39:51 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/21 14:29:02 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_count_valid_env(char *argv[])
{
	char	*equal_pos;

	if (argv == NULL)
		return (-1);
	if (ms_count_str(argv) < 1)
		return (-1);
	equal_pos = ft_strchr(argv[1], '=');
	if (equal_pos == NULL || equal_pos == &argv[1])
		return (false);
	return (true);
}

int	ms_builtin_export(char *argv[])
{
	char		**new_environ;
	size_t		env_size;
	size_t		i;

	if (ms_count_valid_env(argv) < 0)
		return (-1);
	env_size = ms_env_size(environ);
	new_environ = malloc(sizeof(char *) * (env_size + 1 + 1));
	if (new_environ == NULL)
		exit(EXIT_FAILURE);
	ms_strlst_cpy(new_environ, )
}
