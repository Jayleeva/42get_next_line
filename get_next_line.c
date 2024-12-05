/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:16:25 by cyglardo          #+#    #+#             */
/*   Updated: 2024/12/05 10:56:22 by cyglardo         ###   ########.fr       */
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
	while (read_bytes > 0 && (!*stash || strchr_(stash, '\n') == -1)) // (end_of_line(stash) != ft_strlen_(stash) MARCHE PAS //tant que je peux lire ET tant que je n'ai pas trouvé de '\0' OU de '\n' dans stash
	{
		//printf("--READ--");
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(buffer), NULL); // free et clean le buffer ET OU la static ici ne change rien, pourquoi ????
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

	temp = stash;
	stash = ft_substr_(stash, eol +1, ft_strlen_(stash) - eol);
	free(temp);
	return (stash);
}

ssize_t	end_of_line(char *s)
{
	ssize_t	eol;

	eol = 0;
	while (s[eol] && s[eol] != '\n')
		eol ++;
	return (eol);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)  // si fd ou BUFFER_SIZE invalides, ou si (pas autorisation de read?) on arrete tout -> ABSOLUMENT NECESSAIRE
		return (NULL);   //si je laisse le test de read avec le test de fd et BUFFER_SIZE et ne fais que retourner NULL en cas d'erreur, francinette me suggère de clear ma static quand read == -1. Si je le mets à part et ajoute un free(stash) dans le return, francinette me dit que je réutilise un truc déjà free??? alors que y a return et qu'on sort donc de la fonction??????? jpp????
	if (stash == NULL)
		stash = ft_strdup_("");
	stash = read_line(fd, stash);
	if (!stash || !*stash)
		return (free(stash), stash = NULL, NULL); // je libere et clean le stash si pointe sur un '\0'? --> ABSOLUMENT NECESSAIRE DE FREE et CLEAN ICI
	line = extract_line(stash, end_of_line(stash));
	stash = update_stash(stash, end_of_line(stash));
	//if (!stash) --> change rien. Si je mets (!*stash) à la place, leak.
	//	return (free(stash), stash = NULL, NULL);
	//printf("_%s_\n", line);
	return (line);
}
