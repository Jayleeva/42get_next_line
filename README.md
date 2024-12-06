# 42get_next_line
Projet du 2ème cercle 42

# Consignes:
**Créer une fonction qui retourne la prochaine ligne d'un fichier passé en argument.**

# read(int fd, char *buffer, int bytes_to_read)
La fonction read() lit le nombre de bytes reçu en argument depuis le **file descriptor** reçu en argument (identifiant du fichier + mode de lecture sous forme de int) et stocke les bytes lus dans le buffer reçu. 
En cas d'erreur (le fichier n'est pas ou plus lisible), elle retourne -1. Sinon, elle retourne le nombre de bytes effectivement lus. Ainsi, lorsqu'elle arrive en fin de fichier, elle retourne 0.
Tant que le fichier lu n'est pas fermé, la tête de lecture ("curseur") garde sa position d'un appel à l'autre: en appelant read() plusieurs fois de suite avec le même file descriptor, on ne relit pas les mêmes bytes à chaque fois mais bien les suivants. Le nombre de bytes lus à chaque appel dépend de la taille du buffer passée en argument: si le BUFFER_SIZE est à 42, read() lira par tranches de 42 bytes, tant qu'elle n'a pas atteint la fin du fichier ou qu'une erreur se produit.
Elle ne malloc() et ne free() pas, il faut le faire soi-même (créer un buffer, le malloc de la taille de BUFFER_SIZE, le libérer).

# Variable statique
Une variable statique a la particularité de conserver sa valeur d'un appel à l'autre de la fonction où elle est déclarée. Pour déclarer une statique, écrire ``static var_type	var_name;``. 
On s'en sert dans ce projet pour garder en mémoire les derniers bytes lus par read() après un retour à la ligne ('\n').

# Comment nettoyer une variable statique allouée
- D'abord la free().
- PUIS lui assigner NULL (ou 0 pour un int).
Si on assigne NULL avant, on ne peut plus la free(). 


# En gros
## Dans le main
Utiliser open() pour ouvrir un fichier.

Appeler get_next_line tant que le fichier n'a pas été lu en entier.

Utiliser printf() pour imprimer chaque ligne une à une. Utiliser free() pour libérer chaque ligne après impression, puis les réinitialiser à NULL.

Utiliser close() pour fermer le fichier.

## Dans get_next_line
Dans une boucle qui tourne tant qu'on n'a pas lu de retour à la ligne ou de fin de fichier, utiliser la fonction read() pour stocker les bytes lus dans un buffer. Fermer le buffer en le terminant par un '\0' (sinon, parasitage). En cas d'erreur de read(), free() le buffer ET la statique avant de return (NULL).

Utiliser strjoin() pour appondre les nouveaux bytes lus aux précédents dans une **variable statique** de type chaîne de caractères (chez moi, "stash"). A prévoir: si la variable statique est vide avant le strjoin(), il faut lui donner une base, par ex. avec strdup(""). ATTENTION: ne pas oublier de free() entre les allocations de mémoire.

Utiliser strchr() pour vérifier s'il y a un \n dans les bytes lus.

Utiliser substr() pour copier le stash jusqu'au prochain \n ou jusqu'à la fin du fichier dans une chaîne de caractères qui aura valeur de retour.

Utiliser substr() pour garder en stash que les bytes lus après un \n. Comme c'est une variable statique, il faut la nettoyer avant de la réutiliser; read reprendra à la fin de stash.
