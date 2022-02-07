/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:13:22 by adaifi            #+#    #+#             */
/*   Updated: 2022/02/03 17:13:22 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "pipex.h"

static void	execute(char *arg, char **envp)
{
	char	**cmd;
	int		i;

	i = 0;
	if (*arg)
	{
		cmd = ft_split(arg, ' ');
		execve(get_path(envp, cmd[0]), cmd, envp);
		error(cmd[0], "command not found");
	}
	else
	{
		error("", "command not found");
	}
	exit(127);
}

static void	pipex(int fd1, int fd2, char **argv, char **envp)
{
	int		fd[2];
	int		id;

	id = 1;
	pipe(fd);
	if (fd1 != -1)
		id = fork();
	if (id == 0)
	{
		dup2(fd1, 0);
		close(fd[0]);
		dup2(fd[1], 1);
		execute(argv[2], envp);
	}
	else
	{
		dup2(fd2, 1);
		close(fd[1]);
		dup2(fd[0], 0);
		wait(NULL);
		execute(argv[3], envp);
	}
}

int	main(int argc, char **argv, char *envp[])
{
	int	file1;
	int	file2;

	if (argc == 5)
	{
		file1 = open(argv[1], O_CREAT | O_RDONLY, 00664);
		if (file1 == -1)
			error(argv[1], strerror(errno));
		file2 = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 00664);
		if (file2 == -1)
		{
			error(argv[4], strerror(errno));
			return (1);
		}
		pipex(file1, file2, argv, envp);
	}
	ft_putstr_fd("Invalid arguments.\n", 2);
	return (1);
}
