#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

char    		*get_next_line(int fd);
static char		*read_line(int fd, char *line);
static char		*extract_line(char *buffer);
static char 	*join_and_free(char *line_buf, char *chunk);
static char		*update_buffer(buffer);
void			*ft_calloc_(size_t nelem, size_t elsize);
size_t			ft_strlen_(const char *str);
char			*ft_strjoin_(char const *s1, char const *s2);

#endif

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif