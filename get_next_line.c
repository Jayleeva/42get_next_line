#include "get_next_line.h"

//read(int fd, void *buf, size_t count)

char    *get_next_line(int fd)
{
    static size_t   read_octets = 0;
    size_t          start;
    size_t          octets_to_read;
    char            *line;

    octets_to_read = ;
    start = read_octets;
    read_octets += read(fd, line_buff, octets_to_read);
    line = (char *)malloc((read_octets - start +1) * sizeof(char));
    if (line == NULL)
        return (NULL);
    line = line_cpy(line, src, start, read_octets);
    return (line);
}