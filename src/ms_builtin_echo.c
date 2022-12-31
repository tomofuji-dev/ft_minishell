/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:10:25 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/31 12:18:16 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_builtin_echo(char *argv[])
{
	bool		print_nl;
	size_t		start;
	size_t		i;

	if (argv[0] == NULL)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (1);
	}
	print_nl = !(argv[1] && ft_strcmp(argv[1], "-n") == 0);
	start = 2 - print_nl;
	i = start;
	while (argv[i] != NULL)
	{
		if (i > start)
			ft_putstr_fd(" ", STDOUT_FILENO);
		ft_putstr_fd(argv[i++], STDOUT_FILENO);
	}
	if (print_nl)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
