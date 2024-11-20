# 42get_next_line
Projet du 2ème cercle 42


# Pseudo-code:

```get next line (fd)
static char *stash;
char	*buffer;
char	*line;
int	i;

if (stash == NULL)
	stash = calloc_(1, 1);
buffer = malloc((BUFFER_SIZE + 1) * sizeof(char)); / besoin de malloc et free ou read s'en occupe?

while (tant que je tombe pas sur un \n?)  while (strchr) ?
	read(fd, buffer, BUFFER_SIZE);
	stash = strjoin(stash, buffer);
	13_in_stash();
line = strlcpy(line, stash, jusqu'à \n inclu); 
stash = ft_substr(stash, jusqu'à \n inclu, jusqu'à '\0'); comment je free les bits de trop?
free (buffer); / read s'en occupe?
return (line);

13_in_stash()
int	i;
i = 0;
while (stash[i] && stash[i] != "\n")
	i ++;
if (stash[i] != "\n")
	doit continuer le read strjoin 13instash
else
	doit sortir de la boucle, copier le stash dans line avec le \n inclu, puis substr le stash, et return line.
