#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

char    		*get_next_line(int fd);
size_t			ft_strlen_(const char *str);
char            *ft_strdup_(const char *src);
char			*ft_strjoin_(char const *s1, char const *s2);
char			*ft_substr(const char *s, unsigned int start, size_t len);

#endif

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
#endif
