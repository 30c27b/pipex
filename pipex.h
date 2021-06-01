/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancoulon <ancoulon@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 11:43:36 by ancoulon          #+#    #+#             */
/*   Updated: 2021/06/01 16:00:06 by ancoulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stddef.h>
# include <stdint.h>

typedef struct s_pipex
{
	int		infd;
	int		outfd;
	char	*cmd1;
	char	*cmd2;
	int		pipefd[2];
	char	**envp;
	char	*path;
	int		dirfd;
}	t_pipex;

void	error_exit(t_pipex *pipex, char *errmsg);
char	*error_not_found(t_pipex *pipex, char *bin);
t_pipex	parse_args(int argc, char **argv, char **envp);
char	*find_path(t_pipex *pipex, char *bin);

#endif
