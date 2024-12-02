/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:16:25 by cyglardo          #+#    #+#             */
/*   Updated: 2024/12/02 14:47:31 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char	*read_line(int fd, char *stash)
{
	char	*buffer;
	int		read_bytes;
	char	*temp;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	read_bytes = 1;
	while (read_bytes > 0 && (!stash || strchr_(stash, '\n') == -1))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			//stash = update_stash(stash, end_of_line(stash)); // je m'assure que le stash soit mis a jour malgre le probleme de lecture --> change rien en l'etat
			return (free(buffer), buffer = NULL, free(stash), stash = NULL, NULL); // free et clean le buffer ET OU la static ici ne change rien, pourquoi ????
		}
		else if (read_bytes == 0)
			break ;
		buffer[read_bytes] = '\0'; //je m'assure que le buffer soit fermé pour pas que le dernier stash soit rempli d'extra buffers pendant le strjoin
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

	if (!stash)
		return (NULL);
	if (stash[eol] == '\0')
	{
		line = ft_strdup_(stash);
		stash = NULL;
		return (line);
	}
	line = ft_substr_(stash, 0, eol +1);
	return (line);
}

char	*update_stash(char *stash, int eol)
{
	char	*temp;

	if (!stash)
		return (NULL);
	temp = stash;
	stash = ft_substr_(stash, eol +1, ft_strlen_(stash) - eol);
	free(temp);
	return (stash);
}

int	end_of_line(char *s)
{
	int	eol;

	if (!s)
		return (0);
	eol = 0;
	while (s[eol] && s[eol] != '\n')
		eol ++;
	return (eol);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0) // si fd ou BUFFER_SIZE invalides, ou si?? on arrete tout -> ABSOLUMENT NECESSAIRE
		return (NULL);
	if (stash == NULL)
		stash = ft_strdup_("");
//	if (read(fd, stash, BUFFER_SIZE) == -1)    //je libere et clean le stash si le read echoue --> casse tout
//		return (free(stash), stash = NULL, NULL);
	stash = read_line(fd, stash);
	if (!*stash)
		return (free(stash), stash = NULL, NULL); // je libere et clean le stash si son adresse n'existe pas/plus?? --> ABSOLUMENT NECESSAIRE DE FREE et CLEAN ICI
	line = extract_line(stash, end_of_line(stash));
	if (!line)
		return (free(line), free(stash), stash = NULL, NULL); // je libere et clean le stash si la ligne est vide --> ca ne change rien
	stash = update_stash(stash, end_of_line(stash));
	if (!stash)	
		return (free(line), line = NULL, free(stash), NULL);   //je libere le stash s'il est vide // si l'adresse n'existe pas/plus?  --> ca ne change rien
	return (line);
}
