/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:16:25 by cyglardo          #+#    #+#             */
/*   Updated: 2024/11/28 17:00:03 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static int	strchr_(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);	
		i ++;
	}
	return (-1);
}

static char	*read_line(int fd, char *stash)
{
	char		*buffer;
	int		read_bytes;
	char		*temp;
	
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	read_bytes = 1;
	while (read_bytes > 0 && (!stash || strchr_(stash, '\n') == -1))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(buffer), NULL);
		else if (read_bytes == 0)
			break;
		buffer[read_bytes] = '\0';   //je m'assure que le buffer soit fermé pour pas que le dernier stash soit rempli d'extra buffers pendant le strjoin
		temp = stash;
		stash = ft_strjoin_(stash, buffer); //je donne l'adresse pointée par stash à une temporaire pour pouvoir la free après avoir réalloué avec strjoin
		free(temp);
	}
	free(buffer);
	return (stash);
}

static char	*extract_line(char *stash, int eol)
{
	char	*line;
	
	if (stash[eol] == '\0')
	{
		line = ft_strdup_(stash);
		stash = NULL;
		return (line);
	}
	line = ft_substr(stash, 0, eol +1);
	return (line);
}

static char	*update_stash(char *stash, int eol)
{
	char	*temp;
	
	temp = stash;
	stash = ft_substr(stash, eol +1, ft_strlen_(stash) - eol); 
	free(temp);
	return (stash);
}

char    *get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	int		eol;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (stash == NULL)
		stash = ft_strdup_("");
	stash = read_line(fd, stash);
	if (!*stash)
		return (NULL);
	eol = 0;
	while (stash[eol] && stash[eol] != '\n')
		eol ++;
	line = extract_line(stash, eol);
	stash = update_stash(stash, eol);
	return (line);
}
