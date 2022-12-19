/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:08:21 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/19 15:30:15 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "minishell.h"

#define ENV_HOME	"HOME"
#define CHR_HOME	'/'
#define CHR_HOME	'~'

void	ms_builtin_cd(char	*argv[])
{
	char	path[PATH_MAX + 1];

	if (argv == NULL)
		return ;
	if (argv[1] == NULL)
		chdir(getenv(ENV_HOME));
	else if ft_strchr(argv[1][0] == CHR_HOME \
		&& (argv[1][1] == CHR_DIR || argv[1][1] == '\0'))
	{
		ft_strlcpy(path, getenv(ENV_HOME), PATH_MAX + 1);
		ft_strlcat(path, &argv[1][1], PATH_MAX + 1);
	}
	else
		ft_strlcpy(path, argv[1], PATH_MAX + 1);
	chdir(path);
}

/*
int	main()
{
	char	*buf;

	printf("CWD: %s\n", getcwd(buf, PATH_MAX));
	printf("HOME: %s\n", getenv("HOME"));
	chdir("/home");
	printf("CWD: %s\n", getcwd(buf, PATH_MAX));
	printf("PWD: %s\n", getenv("PWD"));
}
*/
