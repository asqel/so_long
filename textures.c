/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:32:20 by axlleres          #+#    #+#             */
/*   Updated: 2025/03/14 19:04:23 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"

void	try_load_texture(t_context *ctx, void **dest, char *path)
{
	int	tmp;

	*dest = mlx_xpm_file_to_image(ctx->mlx, path, &tmp, &tmp);
	if (*dest == NULL)
	{
		free_context(ctx);
		write(2, "Error loading texture\n", 22);
		exit(1);
	}
}

void	init_textures(t_context *ctx)
{
	int	tmp;

	try_load_texture(ctx, &(ctx->coin_sprite), "assets/coin.xpm");
	try_load_texture(ctx, &(ctx->ground_sprite), "assets/ground.xpm");
	try_load_texture(ctx, &(ctx->wall_sprite), "assets/wall.xpm");
	try_load_texture(ctx, &(ctx->exit_sprite[0]), "assets/exit.xpm");
	try_load_texture(ctx, &(ctx->exit_sprite[1]), "assets/exit.xpm");
}

void	free_texture(void *mlx, void *texture)
{
	if (texture != NULL)
		mlx_destroy_image(mlx, texture);
}