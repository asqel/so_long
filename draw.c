/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 20:30:26 by axlleres          #+#    #+#             */
/*   Updated: 2025/03/13 13:53:06 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"


void	draw_obj(int x, int y, t_context *ctx)
{
	int x2 = x * SPRITE_SIZE;
	int y2 = y * SPRITE_SIZE;
	if (ctx->map.map[y][x] == OBJ_WALL)
		mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->wall_sprite, x2, y2);
	else if (ctx->map.map[y][x] == OBJ_EMPTY)
		mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->ground_sprite, x2, y2);
	else if (ctx->map.map[y][x] ==  OBJ_EXIT)
		mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->exit_sprite, x2, y2);
}

void	do_draw(t_context *ctx)
{
	int	x;
	int	y;

	y = 0;
	while (y < ctx->map.height)
	{
		x = 0;
		while (x < ctx->map.width)
		{
			draw_obj(x, y, ctx);
			x++;
		}
		y++;
	}
}