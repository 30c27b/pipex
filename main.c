/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancoulon <ancoulon@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 11:43:55 by ancoulon          #+#    #+#             */
/*   Updated: 2021/06/01 14:59:28 by ancoulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "carbon.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <stdio.h>

static char	*to_full_path(char *bin, char *dir)
{
	char	*path;
	char	*full_path;

	if (dir[str_len(dir) - 1] == '/')
	{
		path = str_dup(dir);
	}
	else
	{
		path = str_join(dir, "/");
	}
	if (path == NULL)
		error_exit(strerror(errno));
	full_path = str_join(path, bin);
	if (full_path == NULL)
		error_exit(strerror(errno));
	free(path);
	return (full_path);
}

static char	*find_path(t_pipex *pipex, char *bin)
{
	size_t	i;
	char	**dirs;
	char	*path;
	int		dirfd;

	i = 0;
	dirs = str_split(pipex->path, ':');
	if (dirs == NULL)
		error_exit(strerror(errno));
	while (dirs[i])
	{
		path = to_full_path(bin, dirs[i]);
		dirfd = open(path, O_RDONLY);
		if (dirfd < 0)
			free(path);
		else
		{
			str_split_free(dirs);
			close(dirfd);
			return (path);
		}
		i++;
	}
	str_split_free(dirs);
	error_not_found(bin);
	return (NULL);
}

static int	cmd1(t_pipex *pipex)
{
	pid_t	pid;
	char	**cmd;
	char	*bin;

	cmd = str_split(pipex->cmd1, ' ');
	if (cmd == NULL)
		error_exit(strerror(errno));
	bin = find_path(pipex, cmd[0]);
	pid = fork();
	if (pid == 0)
	{
		dup2(pipex->infd, STDIN_FILENO);
		dup2(pipex->pipefd[1], STDOUT_FILENO);
		execve(bin, cmd, pipex->envp);
		error_exit(strerror(errno));
	}
	waitpid(pid, NULL, 0);
	close(pipex->pipefd[1]);
	close(pipex->infd);
	str_split_free(cmd);
	free(bin);
	return (0);
}

static int	cmd2(t_pipex *pipex)
{
	pid_t	pid;
	char	**cmd;
	char	*bin;

	cmd = str_split(pipex->cmd2, ' ');
	if (cmd == NULL)
		error_exit(strerror(errno));
	bin = find_path(pipex, cmd[0]);
	pid = fork();
	if (pid == 0)
	{
		dup2(pipex->pipefd[0], STDIN_FILENO);
		dup2(pipex->outfd, STDOUT_FILENO);
		execve(bin, cmd, pipex->envp);
		error_exit(strerror(errno));
	}
	waitpid(pid, NULL, 0);
	close(pipex->pipefd[0]);
	close(pipex->outfd);
	free(bin);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	pipex = parse_args(argc, argv, envp);
	pipex.envp = envp;
	if (pipe(pipex.pipefd) < 0)
		error_exit(strerror(errno));
	cmd1(&pipex);
	cmd2(&pipex);
}
