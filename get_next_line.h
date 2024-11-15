#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

char    *get_next_line(int fd);
char	*line_copy(char *dest, char *src, size_t start, size_t end);

#endif

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif