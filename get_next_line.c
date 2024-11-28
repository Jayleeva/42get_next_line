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

int	strchr_(char *s, char c)
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

char    *get_next_line(int fd)
{
	static char 	*stash;
	char			*buffer;
	char			*line;
	char			*temp;
	char			*temp2;
	int				eol;
	int				read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (stash == NULL)
		stash = ft_strdup_("");
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	read_bytes = 1;
	while (read_bytes > 0 && (!stash || strchr_(stash, '\n') == -1))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (NULL);
		else if (read_bytes == 0)
			break;
		buffer[read_bytes] = '\0';   //je m'assure que le buffer soit fermé pour pas que le dernier stash soit rempli d'extra buffers pendant le strjoin
		temp = stash;
		stash = ft_strjoin_(stash, buffer); //je donne l'adresse pointée par stash à une temporaire pour pouvoir la free après avoir réalloué avec strjoin
		free(temp);
	}
	if (!*stash)
		return (NULL);
	free(buffer);
	//printf("**** %s ******\n", stash);
	eol = 0;
	while (stash[eol] && stash[eol] != '\n')
		eol ++;
	if (stash[eol] == '\0')
	{
		line = ft_strdup_(stash);
		stash = NULL;
		return (line);
	}
	line = ft_substr(stash, 0, eol +1);
	//printf("--- %s ---- \n", stash);
	temp2 = stash;
	stash = ft_substr(stash, eol +1, ft_strlen_(stash) - eol); 
	free(temp2);
	//printf("----\n%s\n------\n", stash);
	//if (stash[eol] == 0 || stash[eol +1] == 0)  // besoin pour la boucle du main, MAIS empeche la derniere ligne d'etre imprimee
	//if (stash == NULL && read_bytes == 0)
	//	return (NULL);
	return (line);
}
