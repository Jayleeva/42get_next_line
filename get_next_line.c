#include "get_next_line.h"
#include <stdio.h>

int	end_of_line(char *chunk)
{
	int	i;

	i = 0;
	while (chunk[i])
	{
		if (chunk[i] == '\n')
			return (i);
		i ++;
	}
	return (-1);
}

char    *get_next_line(int fd)
{
	static char 	*stash;
	char		*buffer;
	char		*line;
	char		*temp;
	int		eol;
	int		read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
        	return (NULL);
	if (stash == NULL)
		stash = ft_strdup_("");
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	read_bytes = 1;
	while (read_bytes > 0 && end_of_line(stash) == -1)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		buffer[read_bytes] = '\0';   //je m'assure que le buffer soit fermé pour pas que le dernier stash soit rempli d'extra buffers pendant le strjoin
		temp = stash;
		stash = ft_strjoin_(stash, buffer); //je donne l'adresse pointée par stash à une temporaire pour pouvoir la free après avoir réalloué avec strjoin
		free(temp);
	}
	free(buffer);
	//printf("****\n%s\n******\n", stash);
	eol = end_of_line(stash);
	line = ft_substr(stash, 0, eol);
	temp = stash;
	stash = ft_substr(stash, eol +1, ft_strlen_(stash) - eol); 
	//printf("----\n%s\n------\n", stash);
	free(temp);
	if (read_bytes == 0)
		return (NULL);
	return(line);
}
