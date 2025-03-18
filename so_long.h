/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:35:59 by axlleres          #+#    #+#             */
/*   Updated: 2025/03/18 12:32:09 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>

# define OBJ_EMPTY '0'
# define OBJ_WALL '1'
# define OBJ_PLAYER 'P'
# define OBJ_COIN 'C'
# define OBJ_EXIT 'E'

# define OBJ_FLOOD '#'

# define ERR_MALLOC -1
# define ERR_OPEN -2
# define ERR_READ -3
# define ERR_BIN -4
# define ERR_NOT_RECT -5
# define ERR_LINE -6
# define ERR_NO_PLAYER -7
# define ERR_NO_COIN -8
# define ERR_NO_EXIT -9
# define ERR_MANY_PLAYER -10
# define ERR_MANY_EXIT -11
# define ERR_NO_WALL -12
# define ERR_ACCESS_PARTS -13
# define ERR_MAX -14

typedef unsigned char	t_obj;

typedef struct s_player
{
	int	x;
	int	y;
	char dir;
	unsigned int move_count;
}	t_player;

#define SPRITE_COOLDOWN_TICK 10
#define SPRITE_SIZE 80
#define FPS 30


typedef struct s_map
{
	t_obj		**map;
	int			width;
	int			height;
	t_player	player;
	int			coins;
}	t_map;

typedef struct s_context
{
	void	*mlx;
	void	*win;
	t_map	map;
	void	*player_sprite[4];// up, right, down, left
	void	*coin_sprite;
	void	*exit_sprite;
	void	*wall_sprite;
	void	*floor_sprite;
}	t_context;

void	*ft_calloc(size_t size);
void	*ft_realloc(void *ptr, size_t n_size, int fill_zero);
void	*ft_malloc(size_t size);
void	ft_free(void *ptr);

char	*read_file(char *path, int *err);
int		parser(t_map *map, char *text, int *err);
int		parse_map(t_map *map, char *path);
int		map_is_valid(t_map *map, int *err);
int		copy_map(t_map *copy, t_map *map);
void	free_map(t_map *map);
int		count_coins(t_map *map);

int		ft_strlen(char *str);
void	set_error(int *err, int value);
void	print_error(int err);
void	ft_memcpy(void *dest, void *src, int n);

void	free_player(t_player *p);

void	do_draw(t_context *ctx);
void	init_context(t_context *context, char *map_path);
void	free_context(t_context *ctx);
void	free_texture(void *mlx, void *texture);
void	free_mlx(t_context *ctx);
void	init_textures(t_context *ctx);

#endif