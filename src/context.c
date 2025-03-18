/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:19:49 by axlleres          #+#    #+#             */
/*   Updated: 2025/03/18 13:19:57 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"
#include <unistd.h>

void	check_map_extension(char *path)
{
	int	len;

	len = 0;
	while (path[len] != '\0')
		len++;
	if (len < 4)
		return (print_stderr("Error map must end in .ber\n"), exit(1));
	if (!(path[len - 4] == '.' && path[len - 3] == 'b'
			&& path[len - 2] == 'e' && path[len - 1] == 'r'))
		return (print_stderr("Error map must end in .ber\n"), exit(1));
}

void	init_context(t_context *context, char *map_path)
{
	int	err;

	check_map_extension(map_path);
	*context = (t_context){0};
	context->need_redraw = 1;
	context->map = (t_map){0};
	err = parse_map(&context->map, map_path);
	if (err != 0)
	{
		free_map(&context->map);
		print_error(err);
		exit(1);
	}
}

void	free_context(t_context *ctx)
{
	free_map(&ctx->map);
	mlx_destroy_window(ctx->mlx, ctx->win);
	ctx->win = NULL;
	free_texture(ctx->mlx, ctx->coin_sprite);
	free_texture(ctx->mlx, ctx->exit_sprite);
	free_texture(ctx->mlx, ctx->floor_sprite);
	free_texture(ctx->mlx, ctx->wall_sprite);
	free_texture(ctx->mlx, ctx->player_sprite[0][0]);
	free_texture(ctx->mlx, ctx->player_sprite[1][0]);
	free_texture(ctx->mlx, ctx->player_sprite[2][0]);
	free_texture(ctx->mlx, ctx->player_sprite[3][0]);
	free_texture(ctx->mlx, ctx->player_sprite[0][1]);
	free_texture(ctx->mlx, ctx->player_sprite[1][1]);
	free_texture(ctx->mlx, ctx->player_sprite[2][1]);
	free_texture(ctx->mlx, ctx->player_sprite[3][1]);
	free_mlx(ctx);
}
