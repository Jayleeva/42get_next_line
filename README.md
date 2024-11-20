# 42get_next_line
Projet du 2ème cercle 42


# Pseudo-code:

```
get next line (fd)
static char *stash;
char	*buffer;
char	*line;
int	i;

if (stash == NULL)
	stash = calloc_(1, 1);
buffer = malloc((BUFFER_SIZE + 1) * sizeof(char)); / read ne malloc pas, il faut le faire soi-même
if (buffer == NULL)
	return (NULL);

while (carriagereturn_in_stash(stash) < ft_strlen(stash)) 
	read(fd, buffer, BUFFER_SIZE);
	stash = strjoin(stash, buffer);
i = carriagereturn_in_stash(stash) + 1;
line = strlcpy(line, stash, i); 
stash = ft_substr(stash, i, jusqu'à '\0'); comment je free les bits de trop?
free (buffer); / read ne free pas, il faut le faire soi-même
return (line);



static int	carriagereturn_in_stash(char *stash)
int	i;
i = 0;
while (stash[i] && stash[i] != "\n")
	i ++;
if (stash[i] != "\n")
	return (0); // pas de \n, doit continuer le read et strjoin; 
else
	return (1); // un \n, doit sortir de la boucle, copier le stash dans line avec le \n inclu, puis substr le stash, et return line.
ou
return index dans tous les cas? si index plus petit que ft_strlen(stash)?
