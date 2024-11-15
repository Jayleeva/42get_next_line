#include "get_next_line.h"

char	*line_copy(char *dest, char *src, size_t start, size_t end)
{
	int		i;

	i = start;
	while (i < end)
	{
		dest[i] = src[i];
		i ++;
	}
	return (dest);
}