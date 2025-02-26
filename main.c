/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:36:47 by axlleres          #+#    #+#             */
/*   Updated: 2025/02/26 16:11:01 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>
#include <X11/keysym.h>
#include <stdlib.h>


typedef struct s_context {
	void	*mlx;
	void	*win;
	void 	*back_buffer;
	void 	*back_buffer_addr;
	int		bpp;
	int		sl;
	int		endian;
	int		x;
	int		y;
} t_context;


int on_destroy(t_context *param) {
	mlx_destroy_image(param->mlx, param->back_buffer);
	mlx_destroy_window(param->mlx, param->win);
	mlx_destroy_display(param->mlx);
	free(param->mlx);
	exit(0);
}

int on_key(int key, t_context *param) {
	if (key == XK_Escape)
		on_destroy(param);

	if (key == XK_w)
		param->y -= 10;
	if (key == XK_s)
		param->y += 10;
	if (key == XK_a)
		param->x -= 10;
	if (key == XK_d)
		param->x += 10;
	return (0);
}

int on_tick(t_context *param) {
	mlx_clear_window(param->mlx, param->win);



	mlx_put_image_to_window(param->mlx, param->win, param->back_buffer, param->x, param->y);
	return (0);
}

int main(int argc, char **argv)
{
	t_context context;

	context = (t_context){0};
	if (argc != 2)
	{
		printf("Usage: %s <map_path>\n", argv[0]);
		return (1);
	}
	test_parser(argv[1]);

	context.mlx = mlx_init();
	context.win = mlx_new_window(context.mlx, 300, 300, "Hello world!");
	context.back_buffer = mlx_new_image(context.mlx, 300, 300);
	context.back_buffer_addr = mlx_get_data_addr(context.back_buffer, &context.bpp, &context.sl, &context.endian);

	mlx_hook(context.win, 17, 0, on_destroy, &context);
	mlx_key_hook(context.win, on_key, &context);
	mlx_loop_hook(context.mlx, on_tick, &context);
	mlx_loop(context.mlx);
	return (0);
}