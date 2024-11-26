#include "get_next_line.h"

//read(int fd, void *buf, size_t count)

size_t	ft_strlen_(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i ++;
	return (i);
}

char	*ft_strdup_(const char *src)
{
	int		i;
	char	*copy;

	copy = (char *) malloc((ft_strlen_(src) +1) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (src[i])
	{
		copy[i] = src[i];
		i ++;
	}
	copy[i] = '\0';
	return (copy);
}

char    *ft_substr(const char *s, unsigned int start, size_t len)
{
    char    *ret;
    char    *src;
    size_t    i;

    ret = malloc(len + 1);
    if (!ret)
        return (0);
    src = (char *)s + start;
    i = 0;
    while (*src && i < len)
        ret[i++] = *src++;
    ret[i] = 0;
    return (ret);
}

char	*ft_strjoin_(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	size;
	char	*result;

	size = ft_strlen_(s1) + ft_strlen_(s2);
	result = (char *)malloc((size + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i ++;
	}
	j = 0;
	while (s2[j])
	{
		result[i + j] = s2[j];
		j ++;
	}
	result[i + j] = '\0';
	return (result);
}