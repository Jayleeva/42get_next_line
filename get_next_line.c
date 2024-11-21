#include "get_next_line.h"

int	ft_strlen_(char *s)
{
	int	length;

	length = 0;
	while (s[length])
		length ++;
	return (length);
}

char	*ft_substr_(char *str, int index)
{
	char	*sub;
	char	len;
	int		m;
	
	len = ft_strlen_(str);
	sub = malloc((len - index) * sizeof(char));
	if (sub == NULL)
		return (NULL);
	m = 0;
	while (str[index])
	{
		sub[m] = str[index];
   		m ++;
		index ++;
	}
	sub[index] = '\0';
	free (str);
	return (sub);
}

char	*ft_strlcpy_(char *dest, char *src, int len)
{
	int	n;

	n = 0;
	while (src[n] && n < len)
	{
		dest[n] = src[n];
		n ++;
	}
	dest[n] = '\0';
	return (dest);
}

char	*ft_strjoin_(char *dest, char *src)
{
	char	*joined;
	int		len;
	int		k;
	int		l;

	len = ft_strlen_(dest) + ft_strlen_(src);
	joined = malloc(len * sizeof(char));
	if (joined == NULL)
		return (NULL);
	k = 0;
	while (dest[k])
	{
		joined[k] = dest[k];
		k ++;
	}
	l = 0;
	while (src[l])
	{
		joined[k + l] = src[l];
		l ++;
	}
	joined[k + l] = '\0';
	return (joined);
}

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

char	*ft_calloc_(int nelem, int elsize)
{
	char	*str;
	int		j;

	str = malloc(nelem * elsize);
	if (str == NULL)
		return (NULL);
	j = 0;
	while (str[j])
	{
		str[j] = '\0';
		j ++;
	}
	return (str);
}

char    *get_next_line(int fd)
{
    static char *last_line;
	char		*buffer;
    char        *current_line;
	int			eol;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
        return (NULL);
	if (last_line == NULL)
		last_line = ft_calloc_(1, 1);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	while (end_of_line(last_line) == -1)
	{
		read(fd, buffer, BUFFER_SIZE);  // gerer si read renvoie -1? ou 0?
		last_line = ft_strjoin_(last_line, buffer);
	}
	free(buffer);
	eol = end_of_line(last_line);
	current_line = malloc((eol + 1) * sizeof(char));
	if (current_line == NULL)
		return (NULL);
	current_line = ft_strlcpy_(current_line, last_line, eol);
	last_line = ft_substr_(last_line, eol);
	return (current_line);
}

    /*last_line = read_line(fd, last_line);
    current_line = extract_line(last_line);
    last_line = update_buffer(last_line);
    return (current_line);*/
