/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:53:38 by cyglardo          #+#    #+#             */
/*   Updated: 2024/11/25 13:29:39 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

/*int main(int argc, char **argv)
{
	int 	file_descriptor;
	char	*buffer;
	char	*next_line;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (0);
	if (argc > 1)
	{
        file_descriptor = open(argv[1], O_RDONLY);
   		while (read(file_descriptor, buffer, BUFFER_SIZE) > 0) //imprime uniquement la fin de la ligne en retirant buffersize chars... (si buffersize = 3, imprime à partir du 4ème char par ex) si je mets >= 0 tourne a l'infini
        {
			next_line = get_next_line(file_descriptor);
			printf("%s", next_line);
		}
		close(file_descriptor);
	}
	else
		printf("Error: please enter file name.");
	return (0);
}*/

int main(int argc, char **argv)
{
	int     file_descriptor;
	char	*next_line;
    int     w;

	if (argc > 1)
	{
        file_descriptor = open(argv[1], O_RDONLY);
		if (file_descriptor < 0)
		{
			printf("Error: could not open file.");
			return (0);
		}
        w = 1;
		while (w == 1)
		{
			next_line = get_next_line(file_descriptor);
			if (next_line == NULL)
            {
                next_line = "(null)";
                w = 0;
            }
			//printf("%s", next_line);
			free(next_line);
			next_line = NULL;
		}
		close(file_descriptor);
	}
	else
		printf("Error: please enter file name.");
	return (0);
}