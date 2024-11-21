/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:53:38 by cyglardo          #+#    #+#             */
/*   Updated: 2024/11/19 13:56:46 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

void    putchar_(char c)
{
    write(1, &c, 1);
}

void    putstr_(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        putchar_(str[i]);
        i ++;
    }
}

int main(int argc, char **argv)
{
	int file_descriptor;

    if (argc > 1)
	{
        file_descriptor = open(argv[1]);
   		while ()
    	{
        	putstr_(get_next_line(file_descriptor));
    	}
		close(file_descriptor);
	else
		printf("Error: please pass file name in argument.");
    return (0);
}
