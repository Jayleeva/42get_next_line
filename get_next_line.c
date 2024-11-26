#include "get_next_line.h"
#include <stdio.h>

int		end_of_line(char *chunk)
{
	int	i;

	i = 0;
	while (chunk[i] && chunk[i] != '\n')
		i ++;
	if (chunk[i] == '\0')
		i = -1;
	//printf("%d\n", i);
	return (i);
}

char    *get_next_line(int fd)
{
    static char *stash;
	char		*buffer;
    char        *line;
	char		*temp;
	int			eol;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
        return (NULL);
	}
	if (stash == NULL)
		stash = ft_strdup_("");
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	while (end_of_line(stash) == -1)
	{
		read(fd, buffer, BUFFER_SIZE);
		temp = stash;
		stash = ft_strjoin_(stash, buffer); //je donne l'adresse pointée par stash à une temporaire pour pouvoir la free après avoir réalloué avec strjoin
		free(temp);
	}
	free(buffer);
	eol = end_of_line(stash);
	line = ft_substr(stash, 0, eol);
	temp = stash;
	stash = ft_substr(stash, eol +1, ft_strlen_(stash) - eol);
	free(temp);
	return(line);
}