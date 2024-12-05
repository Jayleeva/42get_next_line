#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>

char		*get_next_line(int fd);
ssize_t		end_of_line(char *s);
char		*update_stash(char *stash, int eol);
ssize_t		strchr_(char *s, char c);
ssize_t		ft_strlen_(const char *str);
char		*ft_strdup_(const char *src);
char		*ft_strjoin_(char const *s1, char const *s2);
char		*ft_substr_(const char *s, unsigned int start, size_t len);

#endif

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
#endif

#ifndef MAX_FD
# define MAX_FD 1024
#endif
