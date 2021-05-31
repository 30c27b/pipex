/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancoulon <ancoulon@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 11:43:36 by ancoulon          #+#    #+#             */
/*   Updated: 2021/05/31 17:27:57 by ancoulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <stddef.h>
#include <stdint.h>

typedef struct s_pipex
{
	int		infd;
	int		outfd;
	char	*cmd1;
	char	*cmd2;
	int		pipefd[2];
	char	**envp;
}	t_pipex;

size_t	str_len(char *str);
void	str_print(int fd, char *str);
void	error_exit(char *errmsg);
t_pipex	parse_args(int argc, char **argv);
void	*mem_set(void *p, uint8_t c, size_t size);
char	**str_split(char *s, char c);
char	**str_split_free(char **strs);
char	*str_ncpy(char *d, char *s, size_t len);
char	*str_ndup(char *s, size_t len);
void	*mem_calloc(size_t size);
void	*mem_setalloc(size_t size, uint8_t c);

#endif
