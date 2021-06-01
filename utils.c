/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancoulon <ancoulon@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 11:47:25 by ancoulon          #+#    #+#             */
/*   Updated: 2021/06/01 16:11:43 by ancoulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "carbon.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

static void	on_exit(t_pipex *pipex)
{
	if (pipex->infd > 0)
		close (pipex->infd);
	if (pipex->outfd > 0)
		close (pipex->outfd);
	if (pipex->pipefd[0] > 0)
		close (pipex->pipefd[0]);
	if (pipex->pipefd[1] > 0)
		close (pipex->pipefd[1]);
}

void	error_exit(t_pipex *pipex, char *errmsg)
{
	fmt_fprint(2, "pipex: ");
	fmt_fprint(2, errmsg);
	fmt_fprint(2, "\n");
	on_exit(pipex);
	exit(EXIT_FAILURE);
}

char	*error_not_found(t_pipex *pipex, char *bin)
{
	fmt_fprint(2, "pipex: command not found: ");
	fmt_fprint(2, bin);
	fmt_fprint(2, "\n");
	on_exit(pipex);
	exit(EXIT_FAILURE);
	return (NULL);
}

static char	*get_env_path(t_pipex *pipex, char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (str_ncmp(envp[i], "PATH=", 5) == 0)
			return (str_sub(envp[i], 5, str_len(envp[i])));
		i++;
	}
	error_exit(pipex, "The PATH environement variable is not defined.");
	return (NULL);
}

t_pipex	parse_args(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	mem_set(&pipex, 0, sizeof(pipex));
	if (argc != 5)
		error_exit(&pipex, "Invalid number of arguments.");
	pipex.infd = open(argv[1], O_RDONLY);
	if (pipex.infd < 0)
		error_exit(&pipex, strerror(errno));
	pipex.cmd1 = argv[2];
	pipex.cmd2 = argv[3];
	pipex.outfd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pipex.outfd < 0)
		error_exit(&pipex, strerror(errno));
	pipex.path = get_env_path(&pipex, envp);
	if (pipex.path == NULL)
		error_exit(&pipex, strerror(errno));
	return (pipex);
}
