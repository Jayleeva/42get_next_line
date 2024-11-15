#include "get_next_line.h"

static char *update_buffer(buffer)
{
    int i;
    int j;
    char    *line;

    i = 0;
    while (buffer[i] && buffer[i] != '\n')
        i ++;
    if (buffer[i] == NULL)
    {
        free(buffer);
        return (NULL);
    }
    line = ft_calloc_((ft_strlen_(buffer) - i + 1), sizeof(char));
    i ++;
    j = 0;
    while (buffer[i])
        line[j++] = buffer[i++];
    free(buffer);
    return (line);
}

static char *join_and_free(char *line_buf, char *chunk)
{
    char    *joined;

    joined = ft_strjoin_(line_buf, chunk);
    free(line_buf);
    return (joined);
}

static char	*read_line(int fd, char *line_buf)
{
	char	*chunk;
	int		octets_read;

	if (line_buf == NULL)
		line_buf = ft_calloc_(1, 1);
	chunk = ft_calloc_(BUFFER_SIZE + 1, sizeof(char));
	octets_read = 1;
	while (octets_read > 0 )
	{
		octets_read = read(fd, chunk, BUFFER_SIZE);
		if (octets_read == -1)
		{
			free(chunk);
			return (NULL);
		}
		chunk[octets_read] = 0;
		line_buf = join_and_free(line_buf, chunk);
		if (strchr_(chunk, '\n'))
			break;
	}
	free(chunk);
	return (line_buf);
}

static char *extract_line(char *buffer)
{
	char	*line;
	int		i;
	
	if (buffer == NULL)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i ++;
	line = ft_calloc_(i + 2, sizeof(char));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i ++;
	}
	if (buffer[i] && buffer[i] == '\n')
	{
		i ++;
		line[i] = '\n';
	}
	return (line);
}

char    *get_next_line(int fd)
{
    static char *buffer;
    char        *line;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
        return (NULL);
    buffer = read_line(fd, buffer);
    if (buffer == NULL)
        return (NULL);
    line = extract_line(buffer);
    buffer = update_buffer(buffer);
    return (line);
}