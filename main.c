/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:36:47 by axlleres          #+#    #+#             */
/*   Updated: 2025/03/18 13:12:30 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include <stdio.h>
#include <X11/keysym.h>
#include <stdlib.h>
#include <unistd.h>

int	on_destroy(t_context *param)
{
	free_context(param);
	exit(0);
}

void	print_num(unsigned int n)
{
	if (n < 10)
		return ((void) write(1, (n += '0', &n), 1));
	print_num(n / 10);
	print_num(n % 10);
}

void	move_player(t_context *ctx, int dir, int x, int y)
{
	ctx->map.player.dir = dir;
	if (ctx->map.map[y][x] == OBJ_WALL)
		return ;
	ctx->map.player.x = x;
	ctx->map.player.y = y;
	ctx->map.player.move_count++;
	print_num(ctx->map.player.move_count);
	write(1, "\n", 1);
	if (ctx->map.map[y][x] == OBJ_COIN)
	{
		ctx->map.map[y][x] = OBJ_EMPTY;
		ctx->map.coins--;
	}
	else if (ctx->map.map[y][x] == OBJ_EXIT && ctx->map.coins == 0)
	{
		write(1, "Bravo vous avez gagne !\n", 24);
		on_destroy(ctx);
	}
}

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

int	on_tick(t_context *param)
{
	if (param->need_redraw)
	{
		mlx_clear_window(param->mlx, param->win);
		do_draw(param);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_context	context;
	if (argc != 2)
	{
		print_stderr("Usage: ");
		print_stderr(argv[0]);
		print_stderr(" <map_path>\n");
		return (1);
	}
	init_context(&context, argv[1]);
	context.mlx = mlx_init();
	context.win = mlx_new_window(
			context.mlx, context.map.width * SPRITE_SIZE,
			context.map.height * SPRITE_SIZE, "so long");
	mlx_hook(context.win, 17, 0, on_destroy, &context);
	init_textures(&context);
	mlx_key_hook(context.win, &on_key, &context);
	mlx_loop_hook(context.mlx, &on_tick, &context);
	mlx_loop(context.mlx);
	return (0);
}
