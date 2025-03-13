/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 20:30:09 by axlleres          #+#    #+#             */
/*   Updated: 2025/03/01 21:23:08 by axlleres         ###   ########.fr       */
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
		print_stderr("Error no exit in map\n");
	else if (err == ERR_MANY_PLAYER)
		print_stderr("Error too many player in map\n\tonly 1 player\n");
	else if (err == ERR_MANY_EXIT)
		print_stderr("Error many exit in map\n\tonly 1 exit\n");
	else if (err == ERR_NO_WALL)
		print_stderr("Error no wall in map\n\tmap must be enclosed by wall\n");
	else if (err == ERR_ACCESS_PARTS)
		print_stderr("Error some parts are not accessible\n");
}

void	print_error(int err)
{
	if (err == ERR_MALLOC)
		print_stderr("Error while allocating\n");
	else if (err == ERR_OPEN)
		print_stderr("Error while opening file\n");
	else if (err == ERR_READ)
		print_stderr("Error while reading file\n");
	else if (err == ERR_BIN)
		print_stderr("Error file is binary\n");
	else if (err == ERR_NOT_RECT)
		print_stderr("Error map is not rectangular\n");
	else if (err == ERR_LINE)
		print_stderr("Error in map invalid character\n\tallowed: P01EC\n");
	else if (err == ERR_NO_PLAYER)
		print_stderr("Error no player in map\n");
	else if (err == ERR_NO_COIN)
		print_stderr("Error no coin in map\n\tat least 1 coin is required\n");
	else
		print_error2(err);
}
