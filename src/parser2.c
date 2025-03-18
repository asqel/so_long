/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:40:35 by axlleres          #+#    #+#             */
/*   Updated: 2025/03/18 13:42:03 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_walls(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < map->height)
		if (map->map[y++][x] != OBJ_WALL)
			return (-1);
	y = 0;
	x = map->width - 1;
	while (y < map->height)
		if (map->map[y++][x] != OBJ_WALL)
			return (-1);
	y = 0;
	x = 0;
	while (x < map->width)
		if (map->map[y][x++] != OBJ_WALL)
			return (-1);
	y = map->height - 1;
	x = 0;
	while (x < map->width)
		if (map->map[y][x++] != OBJ_WALL)
			return (-1);
	return (0);
}

int	count_coins(t_map *map)
{
	int	x;
	int	y;
	int	count;

	y = 0;
	count = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == OBJ_COIN)
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

void	set_co(int co[4][2])
{
	co[0][0] = -1;
	co[0][1] = 0;
	co[1][0] = 0;
	co[1][1] = -1;
	co[2][0] = 1;
	co[2][1] = 0;
	co[3][0] = 0;
	co[3][1] = 1;
}

int	extend_flood(t_map *map, int y, int x)
{
	int		has_changed;
	int		co[4][2];
	int		i;
	t_obj	*tmp;

	set_co(co);
	i = 0;
	has_changed = 0;
	while (i < 4)
	{
		tmp = &(map->map[y + co[i][1]][x + co[i][0]]);
		if (*tmp == OBJ_EMPTY || *tmp == OBJ_COIN || *tmp == OBJ_EXIT)
		{
			has_changed = 1;
			*tmp = OBJ_FLOOD;
		}
		i++;
	}
	return (has_changed);
}
