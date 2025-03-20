/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:32:20 by axlleres          #+#    #+#             */
/*   Updated: 2025/03/18 15:29:17 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"
#include <unistd.h>

void	try_load_texture(t_context *ctx, void **dest, char *path)
{
	int	tmp;

	*dest = mlx_xpm_file_to_image(ctx->mlx, path, &tmp, &tmp);
	if (*dest == NULL)
	{
		free_context(ctx);
		print_stderr("Error\n\tloading texture \"");
		print_stderr(path);
		print_stderr("\"\n");
		exit(1);
	}
}

void	init_textures(t_context *ctx)
{
	try_load_texture(ctx, &(ctx->coin_sprite), "assets/coin.xpm");
	try_load_texture(ctx, &(ctx->floor_sprite), "assets/ground.xpm");
	try_load_texture(ctx, &(ctx->wall_sprite), "assets/wall.xpm");
	try_load_texture(ctx, &(ctx->exit_sprite), "assets/exit.xpm");
	try_load_texture(ctx, &(ctx->player_sprite[0][0]), "assets/player_u.xpm");
	try_load_texture(ctx, &(ctx->player_sprite[1][0]), "assets/player_r.xpm");
	try_load_texture(ctx, &(ctx->player_sprite[2][0]), "assets/player_d.xpm");
	try_load_texture(ctx, &(ctx->player_sprite[3][0]), "assets/player_l.xpm");
	try_load_texture(ctx, &(ctx->player_sprite[0][1]), "assets/player_ue.xpm");
	try_load_texture(ctx, &(ctx->player_sprite[1][1]), "assets/player_re.xpm");
	try_load_texture(ctx, &(ctx->player_sprite[2][1]), "assets/player_de.xpm");
	try_load_texture(ctx, &(ctx->player_sprite[3][1]), "assets/player_le.xpm");
}

void	free_texture(void *mlx, void *texture)
{
	if (texture != NULL)
		mlx_destroy_image(mlx, texture);
}
