#include "so_long.h"
#include "mlx.h"

void	init_context(t_context *context, char *map_path)
{
	int	err;

	*context = (t_context){0};
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
	int	i;

	free_map(&ctx->map);
	mlx_destroy_window(ctx->mlx, ctx->win);
	ctx->win = NULL;
	free_texture(ctx->mlx, ctx->coin_sprite);
	free_texture(ctx->mlx, ctx->exit_sprite[0]);
	free_texture(ctx->mlx, ctx->exit_sprite[1]);
	free_texture(ctx->mlx, ctx->ground_sprite);
	free_texture(ctx->mlx, ctx->wall_sprite);
	i = 0;
	while (i < 4)
	{
		free_texture(ctx->mlx, ctx->player_sprite[i][0]);
		free_texture(ctx->mlx, ctx->player_sprite[i][1]);
		free_texture(ctx->mlx, ctx->player_sprite[i][2]);
		i++;
	}
	free_mlx(ctx);
}