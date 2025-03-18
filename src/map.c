/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:31:37 by axlleres          #+#    #+#             */
/*   Updated: 2025/03/18 13:19:11 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	copy_map(t_map *copy, t_map *map)
{
	int	i;

	copy->height = map->height;
	copy->width = map->width;
	copy->map = ft_calloc(sizeof(t_obj *) * copy->height);
	if (copy->map == NULL)
		return (-1);
	i = 0;
	while (i < copy->height)
	{
		copy->map[i] = ft_calloc(sizeof(t_obj) * copy->width);
		if (copy->map[i] == NULL)
		{
			while (i >= 0)
				ft_free(copy->map[i--]);
			ft_free(copy->map);
			return (-1);
		}
		ft_memcpy(copy->map[i], map->map[i], sizeof(t_obj) * copy->width);
		i++;
	}
	copy->player = map->player;
	return (0);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		ft_free(map->map[i]);
		i++;
	}
	free_player(&map->player);
	ft_free(map->map);
}

void	free_player(t_player *player)
{
	(void)player;
}
