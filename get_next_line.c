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
	//char		*temp2;
	int			eol;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
        return (NULL);
	}
	if (stash == NULL)
		stash = ft_calloc_(1, sizeof(char));
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
	printf("-----\n");
	printf("%s", stash);
	printf("\n-----\n");

	eol = end_of_line(stash);
	write(1, &stash[eol -1], 1);
	line = ft_calloc_((size_t)33, sizeof(char));
	printf("%zu\n", ft_strlen_(line));
	//line = ft_strlcpy_(line, stash, eol);
	//temp2 = stash;
	//stash = ft_substr_(stash, eol);
	//free(temp2);*/
	//printf("%s", line);
	//return ("test");
	return(line);
}