/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancoulon <ancoulon@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 15:58:31 by ancoulon          #+#    #+#             */
/*   Updated: 2021/06/01 16:04:54 by ancoulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "carbon.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

static char	*to_full_path(t_pipex *pipex, char *bin, char *dir)
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
		error_exit(pipex, strerror(errno));
	full_path = str_join(path, bin);
	if (full_path == NULL)
		error_exit(pipex, strerror(errno));
	free(path);
	return (full_path);
}

static int	is_absolute(char *bin)
{
	if (bin[0] == '/' || bin[0] == '.' || bin[0] == '~')
		return (1);
	return (0);
}

static char	*make_path(t_pipex *pipex, char *bin)
{
	size_t	i;
	char	**dirs;
	char	*path;

	i = 0;
	dirs = str_split(pipex->path, ':');
	if (dirs == NULL)
		error_exit(pipex, strerror(errno));
	while (dirs[i])
	{
		path = to_full_path(pipex, bin, dirs[i]);
		pipex->dirfd = open(path, O_RDONLY);
		if (pipex->dirfd < 0)
			free(path);
		else
		{
			str_split_free(dirs);
			close(pipex->dirfd);
			return (path);
		}
		i++;
	}
	str_split_free(dirs);
	return (error_not_found(pipex, bin));
}

char	*find_path(t_pipex *pipex, char *bin)
{
	char	*path;

	if (is_absolute(bin))
	{
		path = str_dup(bin);
		if (path == NULL)
			error_exit(pipex, strerror(errno));
		return (path);
	}
	return (make_path(pipex, bin));
}
