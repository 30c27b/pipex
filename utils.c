/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancoulon <ancoulon@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 11:47:25 by ancoulon          #+#    #+#             */
/*   Updated: 2021/05/31 17:33:50 by ancoulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

size_t	str_len(char *str)
{
	size_t	i;
	
	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

void	str_print(int fd, char *str)
{
	write(fd, str, str_len(str));
}

void	error_exit(char *errmsg)
{
	str_print(2, "Error: ");
	str_print(2, errmsg);
	str_print(2, "\n");
	exit(EXIT_FAILURE);
}

t_pipex	parse_args(int argc, char **argv)
{
	t_pipex	pipex;

	if (argc != 5)
		error_exit("Invalid number of arguments.");
	pipex.infd = open(argv[1], O_RDONLY);
	if (pipex.infd < 0)
		error_exit(strerror(errno));
	pipex.cmd1 = argv[2];
	pipex.cmd2 = argv[3];
	pipex.outfd = open(argv[4], O_WRONLY | O_CREAT);
	if (pipex.outfd < 0)
		error_exit(strerror(errno));
	return (pipex);
}