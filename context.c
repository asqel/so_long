#include "so_long.h"

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