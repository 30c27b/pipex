/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancoulon <ancoulon@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 17:20:39 by ancoulon          #+#    #+#             */
/*   Updated: 2021/05/31 17:29:00 by ancoulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdlib.h>

void	*mem_set(void *p, uint8_t c, size_t size)
{
	if (p)
		while (size--)
			*(uint8_t *)p++ = c;
	return (p);
}

void	*mem_setalloc(size_t size, uint8_t c)
{
	void	*p;

	p = malloc(size);
	if (p)
		mem_set(p, c, size);
	return (p);
}

void	*mem_calloc(size_t size)
{
	return (mem_setalloc(size, 0b00000000));
}

char	*str_ncpy(char *d, char *s, size_t len)
{
	size_t	i;

	if (d && s)
	{
		i = 0;
		while (s[i] && i < (len - 1))
		{
			d[i] = s[i];
			i++;
		}
		d[i] = '\0';
	}
	return (d);
}

char	*str_ndup(char *s, size_t len)
{
	char	*dup;
	size_t	max_len;

	max_len = str_len(s);
	if (len < max_len)
		max_len = len;
	dup = mem_calloc(max_len);
	str_ncpy(dup, s, len + 1);
	return (dup);
}
