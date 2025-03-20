/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:25:37 by axlleres          #+#    #+#             */
/*   Updated: 2025/03/20 15:43:44 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"
#include <X11/keysym.h>

void	free_mlx(t_context *ctx)
{
	if (ctx->win != NULL)
		mlx_destroy_window(ctx->mlx, ctx->win);
	if (ctx->mlx != NULL)
	{
		mlx_destroy_display(ctx->mlx);
		free(ctx->mlx);
	}
}

int	on_destroy(t_context *param)
{
	free_context(param);
	exit(0);
}

extern void	move_player(t_context *ctx, int dir, int x, int y);

int	on_key(int key, t_context *ctx)
{
	if (key == XK_Escape)
		on_destroy(ctx);
	if (key == XK_w)
		move_player(ctx, 0, ctx->map.player.x, ctx->map.player.y - 1);
	else if (key == XK_s)
		move_player(ctx, 2, ctx->map.player.x, ctx->map.player.y + 1);
	else if (key == XK_a)
		move_player(ctx, 3, ctx->map.player.x - 1, ctx->map.player.y);
	else if (key == XK_d)
		move_player(ctx, 1, ctx->map.player.x + 1, ctx->map.player.y);
	ctx->need_redraw = 1;
	return (0);
}
