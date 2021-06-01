/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancoulon <ancoulon@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 11:43:55 by ancoulon          #+#    #+#             */
/*   Updated: 2021/06/01 16:00:01 by ancoulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "carbon.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

static int	cmd1(t_pipex *pipex)
{
	pid_t	pid;
	char	**cmd;
	char	*bin;

	cmd = str_split(pipex->cmd1, ' ');
	if (cmd == NULL)
		error_exit(pipex, strerror(errno));
	bin = find_path(pipex, cmd[0]);
	pid = fork();
	if (pid == 0)
	{
		dup2(pipex->infd, STDIN_FILENO);
		dup2(pipex->pipefd[1], STDOUT_FILENO);
		execve(bin, cmd, pipex->envp);
		error_exit(pipex, strerror(errno));
	}
	waitpid(pid, NULL, 0);
	close(pipex->infd);
	close(pipex->pipefd[1]);
	pipex->pipefd[1] = -1;
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
		error_exit(pipex, strerror(errno));
	bin = find_path(pipex, cmd[0]);
	pid = fork();
	if (pid == 0)
	{
		dup2(pipex->pipefd[0], STDIN_FILENO);
		dup2(pipex->outfd, STDOUT_FILENO);
		execve(bin, cmd, pipex->envp);
		error_exit(pipex, strerror(errno));
	}
	waitpid(pid, NULL, 0);
	close(pipex->outfd);
	close(pipex->pipefd[0]);
	pipex->pipefd[0] = -1;
	str_split_free(cmd);
	free(bin);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	pipex = parse_args(argc, argv, envp);
	pipex.envp = envp;
	if (pipe(pipex.pipefd) < 0)
		error_exit(&pipex, strerror(errno));
	cmd1(&pipex);
	cmd2(&pipex);
	free(pipex.path);
	system("leaks pipex");
}
