/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:25:37 by axlleres          #+#    #+#             */
/*   Updated: 2025/03/14 16:50:04 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"

void	free_mlx(t_context *ctx)
{
	if (ctx->win != NULL)
		mlx_destroy_window(ctx->mlx, ctx->win);
	if (ctx->mlx != NULL) {
		mlx_destroy_display(ctx->mlx);
		free(ctx->mlx);
	}
}