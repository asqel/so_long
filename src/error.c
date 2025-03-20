/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 20:30:09 by axlleres          #+#    #+#             */
/*   Updated: 2025/03/20 15:39:41 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <unistd.h>

void	print_stderr(char *s)
{
	int	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	write(STDERR_FILENO, s, len);
}

static void	print_error2(int err)
{
	if (err == ERR_NO_EXIT)
		print_stderr("Error\n\tno exit in map\n");
	else if (err == ERR_MANY_PLAYER)
		print_stderr("Error\n\ttoo many player in map\n\tonly 1 player\n");
	else if (err == ERR_MANY_EXIT)
		print_stderr("Error\n\tmany exit in map\n\tonly 1 exit\n");
	else if (err == ERR_NO_WALL)
		print_stderr(
			"Error\n\tno wall in map\n\tmap must be enclosed by wall\n");
	else if (err == ERR_ACCESS_PARTS)
		print_stderr("Error\n\tsome parts are not accessible\n");
	else if (err == ERR_SIZE)
		print_stderr("Error\n\tmap has invalid size\n");
}

void	print_error(int err)
{
	if (err == ERR_MALLOC)
		print_stderr("Error\n\twhile allocating\n");
	else if (err == ERR_OPEN)
		print_stderr("Error\n\twhile opening file\n");
	else if (err == ERR_READ)
		print_stderr("Error\n\twhile reading file\n");
	else if (err == ERR_BIN)
		print_stderr("Error\n\tfile is binary\n");
	else if (err == ERR_NOT_RECT)
		print_stderr("Error\n\tmap is not rectangular\n");
	else if (err == ERR_LINE)
		print_stderr("Error\n\tin map invalid character\n\tallowed: P01EC\n");
	else if (err == ERR_NO_PLAYER)
		print_stderr("Error\n\tno player in map\n");
	else if (err == ERR_NO_COIN)
		print_stderr("Error\n\no coin in map\n\tat least 1 coin needed\n");
	else
		print_error2(err);
}
