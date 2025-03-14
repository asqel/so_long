/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:36:44 by axlleres          #+#    #+#             */
/*   Updated: 2025/03/14 16:56:08 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>

static int get_line_len(char *line)
{
	int	len;

	len = 0;
	while (line[len] != '\n' && line[len] != '\0')
		len++;
	return (len);
}

static int is_obj_legal(char c)
{
	if (c == OBJ_EMPTY || c == OBJ_WALL)
		return (1);
	if (c == OBJ_PLAYER || c == OBJ_COIN)
		return (1);
	if (c == OBJ_EXIT)
		return (1);
	return (0);
}

static t_obj *parse_line(char *line, int len, int *err)
{
	t_obj	*res;
	int		i;

	res = ft_calloc(sizeof(t_obj) * len);
	if (res == NULL)
		return (set_error(err, ERR_MALLOC), NULL);
	i = 0;
	while (i < len)
	{
		if (!is_obj_legal(line[i]))
			return (set_error(err, ERR_LINE), ft_free(res), NULL);
		res[i] = line[i];
		i++;
	}
	return (res);
}

int	parser(t_map *map, char *text, int *err)
{
	int	i;
	t_obj **tmp;

	map->width = -1;

	i = 0;
	while (text[i] != '\0')
	{
		if (text[i] == '\n') {
			i++;
			continue;
		}
		if (map->width == -1)
			map->width = get_line_len(&text[i]);
		else if (map->width != get_line_len(&text[i]))
			return (set_error(err, ERR_NOT_RECT), -1);
		map->height++;
		tmp = ft_realloc(map->map, sizeof(t_obj *) * map->height, 1);
		if (tmp == NULL)
			return (set_error(err, ERR_MALLOC), -1);
		map->map = tmp;
		map->map[map->height - 1] = parse_line(&text[i], map->width, err);
		if (map->map[map->height - 1] == NULL)
			return (-1);
		i += map->width;
	}
	return (0);
}

int parse_map(t_map *map, char *path)
{
	char	*content;
	int		err;

	content = read_file(path, &err);
	if (content == NULL)
		return (err);
	if (parser(map, content, &err) == -1)
		return (ft_free(content), err);
	if (map_is_valid(map, &err) == -1)
		return (ft_free(content), err);
	return (ft_free(content), 0);
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



int	check_walls(t_map *map, int *err)
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

void set_co(int co[4][2])
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

int extend_flood(t_map *map, int y, int x)
{
	int 	has_changed;
	int 	co[4][2];
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

int	do_flood(t_map *map)
{
	int	y;
	int	x;
	int changed;

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

int	check_access(t_map *map, int *err)
{
	map->map[map->player.y][map->player.x] = OBJ_FLOOD;

	while (1)
	{
		if (!do_flood(map))
		{
			if (count_coins(map) == 0 && check_exit(map, err) == -1)
				break;
			else
				return (set_error(err, ERR_ACCESS_PARTS), -1);
		}
	}
	return (set_error(err, 0), 0);

}

int 	map_is_valid(t_map *map, int *err)
{
	t_map	copy;
	int		x;
	int		y;

	if (copy_map(&copy, map) == -1)
		return (set_error(err, ERR_MALLOC), -1);
	if (find_player(&copy, err) == -1)
		return (free_map(&copy), -1);
	if (check_exit(&copy, err) == -1)
		return (free_map(&copy), -1);
	if (check_walls(&copy, err) == -1)
		return  (free_map(&copy), set_error(err, ERR_NO_WALL), -1);
	if (count_coins(&copy) == 0)
		return (free_map(&copy), set_error(err, ERR_NO_COIN), -1);
	if (check_access(&copy, err) == -1)
		return (free_map(&copy), -1);
	free_map(&copy);
	find_player(map, err);
	return (0);
}