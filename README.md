# 42get_next_line
Projet du 2ème cercle 42


# Pseudo-code:

```
get next line (fd)
static char *stash;
char	*buffer;
char	*line;
int	i;
int	read_bytes;

if (stash == NULL)
	stash = calloc_(1, 1);
buffer = malloc((BUFFER_SIZE + 1) * sizeof(char)); / read ne malloc pas, il faut le faire soi-même
if (buffer == NULL)
	return (NULL);
//read_bytes = 1;
while (carriagereturn_in_stash(stash) < ft_strlen(stash)) //  while (read_bytes && tant que pas de \n)
	read_bytes =// read(fd, buffer, BUFFER_SIZE);    //si read_bytes == <0 (error) / si read_bytes == 0 (plus rien a lire)
	stash = strjoin(stash, buffer);
free (buffer); / read ne free pas, il faut le faire soi-même
i = carriagereturn_in_stash(stash) + 1;
line = strlcpy(line, stash, i);
stash = ft_substr(stash, i, jusqu'à '\0'); comment je free les bits de trop?
return (line);



static int	carriagereturn_in_stash(char *stash)
int	i;
i = 0;
while (stash[i] && stash[i] != "\n")
	i ++;
return(i);

