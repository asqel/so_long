/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:36:47 by axlleres          #+#    #+#             */
/*   Updated: 2025/03/14 18:25:46 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include <stdio.h>
#include <X11/keysym.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdlib.h>

int on_destroy(t_context *param) {
	free_context(param);
	exit(0);
}


int on_key(int key, t_context *param) {
	if (key == XK_Escape)
		on_destroy(param);
	if (key == XK_w)
		param->map.player.y -= 1;
	if (key == XK_s)
		param->map.player.y += 1;
	if (key == XK_a)
		param->map.player.x -= 1;
	if (key == XK_d)
		param->map.player.x += 1;
	return (0);
}

int on_tick(t_context *param) {
	struct timeval	t0;
    struct timeval	t1;
	int				time_taken;

    gettimeofday(&t0, NULL);
	mlx_clear_window(param->mlx, param->win);
	do_draw(param);
	gettimeofday(&t1, NULL);
	time_taken = (t1.tv_sec - t0.tv_sec) * 1000000 + (t1.tv_usec - t0.tv_usec);
	if (time_taken < 1000000 / FPS)
		usleep(1000000 / FPS - time_taken);
	return (0);
}

int main(int argc, char **argv)
{
	t_context	context;
	int			tmp;

	if (argc != 2)
		return (printf("Usage: %s <map_path>\n", argv[0]), 1);
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