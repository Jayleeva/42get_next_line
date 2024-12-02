/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:53:38 by cyglardo          #+#    #+#             */
/*   Updated: 2024/12/02 08:54:58 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int     file_descriptor;
	char	*next_line;

	if (argc > 1)
	{
		file_descriptor = open(argv[1], O_RDONLY);
		if (file_descriptor < 0)
		{
			printf("Error: could not open file.");
			return (1);
		}
		/*next_line = get_next_line(file_descriptor);
		printf("%s\n", next_line);
		next_line = get_next_line(file_descriptor);
		printf("%s\n", next_line);
		next_line = get_next_line(file_descriptor);
		printf("%s\n", next_line);
		next_line = get_next_line(file_descriptor);
		printf("%s\n", next_line);*/
		
		while (1)
		{
			next_line = get_next_line(file_descriptor);
			if (next_line == NULL)
				break;
			printf("%s", next_line);
			free(next_line);
			next_line = NULL;
		}
		close(file_descriptor);
		free(next_line);
	}
	else
		printf("Error: please enter file name.");
	return (0);
}
