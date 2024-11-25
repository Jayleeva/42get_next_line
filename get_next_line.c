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
	return (i);
}

char    *get_next_line(int fd)
{
    static char *stash;
	char		*buffer;
    char        *line;
	int			eol;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
        return (NULL);
	if (stash == NULL)
		stash = ft_calloc_(1, sizeof(char));
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	while (end_of_line(stash) == -1)
	{
		read(fd, buffer, BUFFER_SIZE);
		stash = ft_strjoin_(stash, buffer);
		printf("%s\n", stash);
	}
	//printf("%s", stash);
	free(buffer);
	eol = end_of_line(stash);
	printf("%d", eol);
	line = ft_calloc_(eol + 1, sizeof(char));
	if (line == NULL)
		return (NULL);
	line = ft_strlcpy_(line, stash, eol);
	stash = ft_substr_(stash, eol);
	return (line);
}