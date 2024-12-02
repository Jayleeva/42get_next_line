#include "get_next_line.h"

int	strchr_(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);	
		i ++;
	}
	return (-1);
}

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

char    *ft_substr_(const char *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;
	size_t	j;

	result = malloc((len + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	i = start;
	j = 0;
	while (i < start + len)
	{
        	result[j] = s[i];
		j ++;
		i ++;
	}
	result[j] = '\0';
	return (result);
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
