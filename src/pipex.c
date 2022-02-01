# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>

# include "pipex.h"

static void	execute(char **cmd, char **envp)
{
	char	*path;

	if (!ft_strchr(cmd[0], '/'))
	{
		path = get_path(envp, cmd[0]);
		execve(path, cmd, envp);
		error(cmd[0], "command not found");
	}
	else
	{
		path = cmd[0];
		if (access(path, X_OK))
			error(path, strerror(errno));
		else
			execve(path, cmd, envp);
	}
}

static void	run(char *arg, char **envp)
{
	char	**cmd;
	int		i;

	i = 0;
	if (*arg)
	{
		cmd = ft_split(arg, ' ');
		execute(cmd, envp);
		while (cmd[i])
			free(cmd[i++]);
		free(cmd);
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
	id = fork();
	if (id == 0)
	{
		dup2(fd1, 0);
		close(fd[0]);
		dup2(fd[1], 1);
		run(argv[2], envp);
	}
	else
	{
		dup2(fd2, 1);
		close(fd[1]);
		dup2(fd[0], 0);
		wait(NULL);
		run(argv[3], envp);
	}
}

int	main(int argc, char **argv, char *envp[])
{
	int	file1;
	int	file2;

	if (argc == 5)
	{
		file1 = open(argv[1], O_CREAT | O_RDWR, 0777);
		if (file1 == -1)
			error(argv[1], strerror(errno));
		file2 = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (file2 == -1)
		{
			error(argv[4], strerror(errno));
			return (0);
		}
		pipex(file1, file2, argv, envp);
	}
	ft_putstr_fd("Invalid arguments.\n", 2);
	return (0);
}
