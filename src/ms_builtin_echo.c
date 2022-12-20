/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:10:25 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/20 11:35:02 by tfujiwar         ###   ########.fr       */
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
		ft_putstr_fd("\n", STDOUT);
		return (1);
	}
	print_nl = !(argv[1] && ft_strcmp(argv[1], "-n") == 0);
	start = 2 - print_nl;
	i = start;
	while (argv[i] != NULL)
	{
		if (i > start)
			ft_putstr_fd(" ", STDOUT);
		ft_putstr_fd(argv[i++], STDOUT);
	}
	if (print_nl)
		ft_putstr_fd("\n", STDOUT);
	return (0);
}

//  gcc src/ms_builtin_echo.c libft/libft.a -I include -I libft/include -o echo
// ./echo
// ./echo abc def
// ./echo -n abc def
int	main(int argc, char *argv[])
{
	return (ms_builtin_echo(argv));
}
