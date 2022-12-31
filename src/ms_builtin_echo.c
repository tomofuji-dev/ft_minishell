/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:10:25 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/31 14:19:05 by Yoshihiro K      ###   ########.fr       */
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
		ft_putchar_fd(CHR_NL, STDOUT_FILENO);
		return (1);
	}
	print_nl = !(argv[1] && ft_strcmp(argv[1], OPTION_NONL) == 0);
	start = 2 - print_nl;
	i = start;
	while (argv[i] != NULL)
	{
		if (i > start)
			ft_putchar_fd(CHR_SPACE, STDOUT_FILENO);
		ft_putstr_fd(argv[i++], STDOUT_FILENO);
	}
	if (print_nl)
		ft_putchar_fd(CHR_NL, STDOUT_FILENO);
	return (0);
}
