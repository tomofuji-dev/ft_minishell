/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:47:24 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/13 15:53:38 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	test_print_argv(int argc, char *argv[])
{
	int	i;

	i = 0;
	while (i < argc)
	{
		printf("argv[%d]: {%s}\n", i, argv[i]);
		i++;
	}
	return ;
}

int	main(int argc, char *argv[])
{
	if (argc > 1)
		test_print_argv(argc, argv);
	return (0);
}
