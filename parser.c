/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:36:44 by axlleres          #+#    #+#             */
/*   Updated: 2025/02/26 16:32:22 by axlleres         ###   ########.fr       */
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

static t_obj *parse_line(char *line, int len)
{
	t_obj	*res;
	int		i;

	res = ft_calloc(sizeof(t_obj) * len);
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (!is_obj_legal(line[i]))
			return (ft_free(res), NULL);
		res[i] = line[i];
		i++;
	}
	return (res);
}

int	parser(t_map *map, char *text)
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
			return (-1);
		map->height++;
		tmp = ft_realloc(map->map, sizeof(t_obj *) * map->height, 1);
		if (tmp == NULL)
			return (-1);
		map->map = tmp;
		map->map[map->height - 1] = parse_line(&text[i], map->width);
		if (map->map[map->height - 1] == NULL)
			return (-1);
		i += map->width;
	}
	return (0);
}

int		is_map_valid(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == OBJ_PLAYER)
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

void test_parser(char *path)
{

	t_map	map = {0};
	char	*content;

	content = read_file(path);
	if (content == NULL)
	{
		printf("Error\n");
		return ;
	}
	if (parser(&map, content) == -1)
	{
		printf("Error2\n");
		return ;
	}
	if (is_map_valid(&map) == 0)
	{
		printf("Error3\n");
		return ;
	}

	int y = 0;
	while (y < map.height)
	{
		int x = 0;
		while (x < map.width)
		{
			printf("%c", map.map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}

	ft_free(content);

}