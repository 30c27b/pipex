/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancoulon <ancoulon@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 11:43:55 by ancoulon          #+#    #+#             */
/*   Updated: 2021/05/31 17:33:58 by ancoulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

static int	cmd1(t_pipex *pipex)
{
	pid_t	pid;
	char	**cmd;

	cmd = str_split(pipex->cmd1, ' ');
	if (cmd == NULL)
		error_exit(strerror(errno));
	pid = fork();
	if (pid == 0)
	{
		dup2(pipex->infd, STDIN_FILENO);
		dup2(pipex->pipefd[1], STDOUT_FILENO);
		execve(cmd[0], cmd, pipex->envp);
	}
	waitpid(pid, NULL, 0);
	close(pipex->pipefd[1]);
	close(pipex->infd);
	return (0);
}

static int	cmd2(t_pipex *pipex)
{
	pid_t	pid;
	char	**cmd;

	cmd = str_split(pipex->cmd2, ' ');
	if (cmd == NULL)
		error_exit(strerror(errno));
	pid = fork();
	if (pid == 0)
	{
		dup2(pipex->pipefd[0], STDIN_FILENO);
		dup2(pipex->outfd, STDOUT_FILENO);
		execve(cmd[0], cmd, pipex->envp);
	}
	waitpid(pid, NULL, 0);
	close(pipex->pipefd[0]);
	close(pipex->outfd);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	pipex = parse_args(argc, argv);
	pipex.envp = envp;
	if (pipe(pipex.pipefd) < 0)
		error_exit(strerror(errno));
	cmd1(&pipex);
	cmd2(&pipex);
}
