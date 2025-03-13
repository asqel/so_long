/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:36:47 by axlleres          #+#    #+#             */
/*   Updated: 2025/03/13 15:49:27 by axlleres         ###   ########.fr       */
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
	mlx_destroy_window(param->mlx, param->win);
	mlx_destroy_display(param->mlx);
	free(param->mlx);
	exit(0);
}

#define FPS 30

int on_key(int key, t_context *param) {
	if (key == XK_Escape)
		on_destroy(param);

	if (key == XK_w)
		param->map.player.y -= 10;
	if (key == XK_s)
		param->map.player.y += 10;
	if (key == XK_a)
		param->map.player.x -= 10;
	if (key == XK_d)
		param->map.player.x += 10;
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
	t_context context;

	if (argc != 2)
	{
		printf("Usage: %s <map_path>\n", argv[0]);
		return (1);
	}
	init_context(&context, argv[1]);
	int tmp;
	context.mlx = mlx_init();
	context.win = mlx_new_window(
			context.mlx, context.map.width * SPRITE_SIZE,
			context.map.height * SPRITE_SIZE, "so long");
	context.coin_sprite = mlx_xpm_file_to_image(context.mlx, "assets/coin.xpm", &tmp, &tmp);
	context.wall_sprite = mlx_xpm_file_to_image(context.mlx, "assets/wall.xpm", &tmp, &tmp);
	context.ground_sprite = mlx_xpm_file_to_image(context.mlx, "assets/ground.xpm", &tmp, &tmp);
	mlx_hook(context.win, 17, 0, on_destroy, &context);
	mlx_key_hook(context.win, on_key, &context);
	mlx_loop_hook(context.mlx, on_tick, &context);
	mlx_loop(context.mlx);
	return (0);
}