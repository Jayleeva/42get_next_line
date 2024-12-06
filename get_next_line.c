/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:16:25 by cyglardo          #+#    #+#             */
/*   Updated: 2024/12/05 13:58:58 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char *stash)
{
	char	*buffer;
	int		read_bytes;
	char	*temp;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (free(stash), NULL);
	read_bytes = 1;
	while (read_bytes > 0 && (!*stash || strchr_(stash, '\n') == -1)) //tant que je peux lire ET tant que je n'ai pas trouvé de '\0' OU de '\n' dans stash
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(buffer), free(stash), NULL);
		else if (read_bytes == 0)
			break ;
		buffer[read_bytes] = '\0'; 
		temp = stash;
		stash = ft_strjoin_(stash, buffer); 
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

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (stash == NULL)
		stash = ft_strdup_("");
	stash = read_line(fd, stash);
	if (!stash || !*stash)
		return (free(stash), stash = NULL, NULL); // je libere et clean le stash s'il est vide || si pointe sur un '\0' --> ABSOLUMENT NECESSAIRE DE FREE et CLEAN ICI
	line = extract_line(stash, end_of_line(stash));
	stash = update_stash(stash, end_of_line(stash));
	return (line);
}
