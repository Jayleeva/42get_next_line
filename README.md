# 42get_next_line
Projet du 2ème cercle 42

# Consignes:
**Créer une fonction qui retourne la prochaine ligne d'un fichier passé en argument.**

# Notions importantes
## read()
``read(int fd, char *buffer, int bytes_to_read)``

La fonction read() lit le nombre de bytes reçu en argument depuis le **file descriptor** reçu en argument (identifiant du fichier + mode d'accès, sous forme de int) et stocke les bytes lus dans le **buffer** reçu.

En cas d'erreur (le fichier n'est pas ou plus lisible), elle retourne -1. Sinon, elle retourne le nombre de bytes effectivement lus. Ainsi, lorsqu'elle arrive en fin de fichier, elle retourne 0.

Tant que le fichier lu n'est pas fermé, la tête de lecture ("curseur") garde sa dernière position d'un appel à l'autre: en appelant read() plusieurs fois de suite avec le même file descriptor, on ne relit pas les mêmes bytes à chaque fois mais bien les suivants. Le nombre de bytes lus à chaque appel dépend de la taille du buffer passée en argument: si le BUFFER_SIZE est à 42, read() lira par tranches de 42 bytes, tant qu'elle n'a pas atteint la fin du fichier ou qu'une erreur se produit.

Elle ne malloc() et ne free() pas, il faut le faire soi-même (créer un buffer, lui allouer la taille de BUFFER_SIZE, le libérer).

## File descriptor
Indique où lire ou écrire. Jusqu'ici, quand on utilisait write(), on lui donnait toujours comme fd = 1, soit le terminal. Dans ce projet avec read(), on donne comme file descriptor le fichier de notre choix, avec le mode d'accès de notre choix (read only, write only, read and write). 

Il faut ouvrir le fichier en spécifiant le mode d'accès pour pouvoir utiliser read() ou write() dessus. Ecrire ``file_descriptor = open(file_name, O_RDONLY)`` par ex.

## Buffer
Variable "tampon" qui permet de stocker temporairement des valeurs entre 2 processus par ex.

## Variable statique
Une variable statique a la particularité de conserver sa valeur d'un appel à l'autre de la fonction où elle est déclarée. Pour déclarer une statique, écrire ``static var_type	var_name;``. 
On s'en sert dans ce projet pour garder en mémoire les derniers bytes lus par read() après un retour à la ligne ``('\n')``.

## Comment nettoyer une variable allouée qu'on compte réallouer (sans leaks)
- D'abord la free().
- PUIS lui assigner NULL (ou 0 pour un int).

Si on assigne NULL avant, on ne peut plus la free().

## Utiliser des temporaires pour réallouer (sans leaks)
Les temporaires prennent l'adresse actuelle de la variable, et on les free() une fois la nouvelle adresse reçue:
```
temp = allocated_var;
allocated_var = allocating_memory_function()
free(temp);
```

# En gros
## Dans le main
Utiliser **open()** pour ouvrir un fichier en mode lecture seulement. Stocker la valeur dans la variable du file descriptor. Vérifier si cette valeur est valide.

Appeler **get_next_line()** tant que le fichier n'a pas été lu en entier.

Utiliser **printf()** pour imprimer chaque ligne une à une. Utiliser **free()** pour libérer chaque ligne après impression, puis les réinitialiser à NULL.

Utiliser **close()** pour fermer le fichier.

## Dans get_next_line
Dans une boucle qui tourne tant qu'on n'a pas lu de retour à la ligne ou de fin de fichier, utiliser la fonction **read()** pour stocker les bytes lus dans un buffer. Fermer le buffer en le terminant par un '\0' (sinon, parasitage). En cas d'erreur de read(), **free()** le buffer ET la statique avant de return (NULL).

Utiliser **strjoin()** pour appondre les nouveaux bytes lus aux précédents dans une **variable statique** de type chaîne de caractères (chez moi, "stash"). A prévoir: si la variable statique est vide avant le strjoin(), il faut lui donner une base, par ex. avec **strdup("")**. ATTENTION: ne pas oublier de free() entre les allocations de mémoire.

Utiliser **strchr()** pour vérifier s'il y a un \n dans les bytes lus.

Utiliser **substr()** pour copier le stash jusqu'au prochain \n ou jusqu'à la fin du fichier dans une chaîne de caractères qui aura valeur de retour.

Utiliser **substr()** pour garder en stash que les bytes lus après un \n. Comme c'est une variable statique, il faut la nettoyer avant de la réutiliser; read reprendra à la fin de stash.

# Bonus
Les bonus de ce projet sont, pour une fois, assez accessibles, surtout si votre get_next_line de base est déjà fait avec une seule variable statique. Pour permettre à votre fonction de jongler entre plusieurs fichiers, il suffit de faire de votre statique non pas un `char*` mais bien un `char**`. Ainsi, vous pouvez y stocker les lignes de plusieurs fichiers. Faites les modifications nécessaires dans votre fonction get_next_line(), en précisant ``var_static[fd]`` partout où vous aviez ``var_static`` et en donnant une taille max à votre tableau (= le nombre max de fichiers lisibles en même temps) lors de la déclaration `static char	*var_static[MAX_FD]`, et voilà.

Attention, cela nécessite d'ajouter un `ifndef` à votre header, qui définira la valeur de `MAX_FD` (le nombre maximal de fichiers gérables par votre fonction). Ce nombre varie en fonction de l'ordinateur sur lequel elle est appelée. Pour le connaître, utilisez la commande `ulimit -n`.

# ATTENTION
La difficulté majeure dans ce projet consiste à gérer les **leaks**. N'oubliez pas:
- La commande ``leaks --atExit -- ./your_program`` à l'exécution vous permet de savoir s'il y a des leaks et si oui, de combien.
- Des leaks se créent lors de la réallocation: par ex, strdup(), strjoin(), substr() utilisent malloc(). Si vous faites appel à ces fonctions plusieurs fois sur la même variable, il faut la nettoyer entre chaque appel, ou utiliser des temporaires.
- Utiliser ``if (read(fd, 0, 0) < 0)`` au lancement de votre get_next_line pour gérer les cas où le fichier ne serait pas ou plus lisible semble causer problème. Utilisez plutôt ``if (read(fd, buffer, BUFFER_SIZE) == -1)`` dans votre boucle de lecture: cela prend en charge le cas ET vous permet de free() le stash proprement.

