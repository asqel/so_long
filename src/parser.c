/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:36:44 by axlleres          #+#    #+#             */
/*   Updated: 2025/03/18 13:47:08 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>

int	get_line_len(char *line)
{
	int	len;

	len = 0;
	while (line[len] != '\n' && line[len] != '\0')
		len++;
	return (len);
}

int	is_obj_legal(char c)
{
	if (c == OBJ_EMPTY || c == OBJ_WALL)
		return (1);
	if (c == OBJ_PLAYER || c == OBJ_COIN)
		return (1);
	if (c == OBJ_EXIT)
		return (1);
	return (0);
}

t_obj	*parse_line(char *line, int len, int *err)
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
	int		i;
	t_obj	**tmp;

	map->width = get_line_len(&text[0]);
	i = 0;
	while (text[i] != '\0')
	{
		if (text[i] == '\n')
		{
			i++;
			continue ;
		}
		if (map->width != get_line_len(&text[i]))
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

int	parse_map(t_map *map, char *path)
{
	char	*content;
	int		err;

	content = read_file(path, &err);
	if (content == NULL)
		return (err);
	if (parser(map, content, &err) == -1)
		return (ft_free(content), err);
	if (map->height == 0 || map->width == 0)
		return (ft_free(content), ERR_SIZE);
	if (map_is_valid(map, &err) == -1)
		return (ft_free(content), err);
	map->coins = count_coins(map);
	return (ft_free(content), 0);
}
