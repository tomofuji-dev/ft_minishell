/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:16:18 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/06 14:52:30 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libc.h>
#include <stdbool.h>

extern char	**environ;
char *first[] = {"/bin/ls", NULL};
char *second[] = {"/bin/cat", NULL};
char **lis[] = {first, second, NULL};

void	close_pipe(int pipe[2])
{
	close(pipe[0]);
	close(pipe[1]);
}

void	copy_pipe(int dest[2], int src[2])
{
	dest[0] = src[0];
	dest[1] = src[1];
}

int	exec_cmd(char **cmd_lis, int prev_pipe[2], int now_pipe[2])
{
	int		fd[2] = {0, 0};
	pid_t	pid;

	fd[0] = prev_pipe[0];
	fd[1] = now_pipe[1];
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[0], 0);
		dup2(fd[1], 1);
		if (fd[0] != 0)
			close(fd[0]);
		if (fd[1] != 1)
			close(fd[1]);
		return (execve(cmd_lis[0], cmd_lis, environ));
	}
	else
		return (pid);
}

int	main(void)
{
	int	prev_pipe[2] = {0, 0};
	int	now_pipe[2];
	int	pid[2];
	int	*status;
	int	i = 0;

	while (i < sizeof(lis) / sizeof(lis[0]) - 1)
	{
		pipe(now_pipe);
		if (lis[i + 1] == NULL)
			now_pipe[1] = 1;
		pid[i] = exec_cmd(lis[i], prev_pipe, now_pipe);
		copy_pipe(prev_pipe, now_pipe);
		i++;
	}
	waitpid(pid[0], status, 1);
	waitpid(pid[1], status, 1);
	return (0);
}
