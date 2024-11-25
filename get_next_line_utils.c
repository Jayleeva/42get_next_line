#include "get_next_line.h"

//read(int fd, void *buf, size_t count)

void	*ft_calloc_(size_t nelem, size_t elsize)
{
	int		*ptr;
	size_t	i;

	ptr = malloc(nelem * elsize);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < nelem * elsize)
	{
		ptr[i] = 0;
		i ++;
	}
	return ((void *)ptr);
}


size_t	ft_strlen_(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i ++;
	return (i);
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

