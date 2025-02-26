/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:35:59 by axlleres          #+#    #+#             */
/*   Updated: 2025/02/26 16:14:33 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>

#define OBJ_EMPTY '0'
#define OBJ_WALL '1'
#define OBJ_PLAYER 'P'
#define OBJ_COIN 'C'
#define OBJ_EXIT 'E'

typedef unsigned char t_obj;

typedef struct s_player {
	int		x;
	int		y;
	int 	coins;
} t_player;

typedef struct s_map {
	t_obj		**map;
	int			width;
	int			height;
	t_player	player;
} t_map;

void	*ft_calloc(size_t size);
void	*ft_realloc(void *ptr, size_t n_size, int fill_zero);
void	*ft_malloc(size_t size);
void	ft_free(void *ptr);

char	*read_file(char *path);
int		parser(t_map *map, char *text);

int		ft_strlen(char *str);

#endif