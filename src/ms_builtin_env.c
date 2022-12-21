/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:39:36 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/20 11:51:28 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_builtin_env(char *argv[])
{
	extern char	**environ;
	size_t		i;

	if (argv == NULL)
		return (0);
	i = 0;
	while (environ[i] != NULL)
		ft_putendl_fd(environ[i++], STDOUT);
	return (0);
}
