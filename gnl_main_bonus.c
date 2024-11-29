/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_main_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:53:38 by cyglardo          #+#    #+#             */
/*   Updated: 2024/11/28 17:00:06 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int     file_descriptor;
	char	*next_line;
	int	i;

	if (argc > 1)
	{
		i = 1;
		while (i < argc)
		{
			file_descriptor = open(argv[i], O_RDONLY);
			i ++;
			if (file_descriptor < 0)
			{
				printf("Error: could not open file.");
				return (1);
			}
			next_line = get_next_line(file_descriptor);
			printf("%s", next_line);
			free(next_line);
			next_line = NULL;
			/*while (1)
			{
				next_line = get_next_line(file_descriptor);
				if (next_line == NULL)
					break;
				printf("%s", next_line);
				free(next_line);
				next_line = NULL;
			}*/
			close(file_descriptor);
			free(next_line);
		}
	}
	else
		printf("Error: please enter file name.");
	return (0);
}
