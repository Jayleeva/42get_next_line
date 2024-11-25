#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

char    		*get_next_line(int fd);
size_t			ft_strlen_(const char *str);
void			*ft_calloc_(size_t nelem, size_t elsize);
char			*ft_strjoin_(char const *s1, char const *s2);
char			*ft_substr_(char *str, int index);
char			*ft_strlcpy_(char *dest, char *src, int len);

#endif

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 3
#endif
