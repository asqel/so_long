/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:42:32 by axlleres          #+#    #+#             */
/*   Updated: 2025/03/18 13:47:14 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_exit(t_map *map, int *err)
{
	int	y;
	int	x;
	int	found;

	found = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == OBJ_EXIT)
				found++;
			x++;
		}
		y++;
	}
	if (found == 0)
		return (set_error(err, ERR_NO_EXIT), -1);
	if (found > 1)
		return (set_error(err, ERR_MANY_EXIT), -1);
	return (0);
}

int	do_flood(t_map *map)
{
	int	y;
	int	x;
	int	changed;

	y = 0;
	changed = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == OBJ_FLOOD)
				if (extend_flood(map, y, x))
					changed = 1;
			x++;
		}
		y++;
	}
	return (changed);
}

int	map_is_valid(t_map *map, int *err)
{
	t_map	copy;

	if (copy_map(&copy, map) == -1)
		return (set_error(err, ERR_MALLOC), -1);
	if (find_player(&copy, err) == -1)
		return (free_map(&copy), -1);
	if (check_exit(&copy, err) == -1)
		return (free_map(&copy), -1);
	if (check_walls(&copy) == -1)
		return (free_map(&copy), set_error(err, ERR_NO_WALL), -1);
	if (count_coins(&copy) == 0)
		return (free_map(&copy), set_error(err, ERR_NO_COIN), -1);
	if (check_access(&copy, err) == -1)
		return (free_map(&copy), -1);
	free_map(&copy);
	find_player(map, err);
	return (0);
}

int	find_player(t_map *map, int *err)
{
	int	y;
	int	x;
	int	found;

	found = 0;
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (map->map[y][x] == OBJ_PLAYER)
			{
				map->player.x = x;
				map->player.y = y;
				map->map[y][x] = OBJ_EMPTY;
				found++;
			}
		}
	}
	if (found == 0)
		return (set_error(err, ERR_NO_PLAYER), -1);
	if (found > 1)
		return (set_error(err, ERR_MANY_PLAYER), -1);
	return (0);
}

int	check_access(t_map *map, int *err)
{
	map->map[map->player.y][map->player.x] = OBJ_FLOOD;
	while (1)
	{
		if (!do_flood(map))
		{
			if (count_coins(map) == 0 && check_exit(map, err) == -1)
				break ;
			else
				return (set_error(err, ERR_ACCESS_PARTS), -1);
		}
	}
	return (set_error(err, 0), 0);
}
