#include <stdint.h>
#include <stdio.h>

#include "cub3d.h"

static void	print_color(const char *label, t_color *c)
{
	if (!c)
		printf("%s: (null)\n", label);
	else
		printf("%s: R=%u G=%u B=%u\n", label, c->code.r, c->code.g, c->code.b);
}

// static void	print_player(const t_player *p)
// {
// 	printf("Player:\n");
// 	printf("  pos   = (%.3f, %.3f)\n", p->pos.x, p->pos.y);
// 	printf("  dir   = (%.3f, %.3f)\n", p->dir.x, p->dir.y);
// 	printf("  plane = (%.3f, %.3f)\n", p->plane.x, p->plane.y);
// }

void	print_grid(const t_grid *g)
{
	int32_t	y;

	printf("--- t_grid ---\n");
	printf("Dimensions: %d x %d\n", g->dim.x, g->dim.y);
	printf("Grid:\n");
	if (g->grid)
	{
		y = 0;
		while (y < g->dim.y)
		{
			printf("%s\n", g->grid[y]);
			y++;
		}
	}
	else
		printf("(null)\n");
	printf("-------------\n");
}

void	print_map(const t_map *m)
{
	const char	*dir;

	if (!m)
	{
		printf("t_map: (null)\n");
		return ;
	}
	printf("=== t_map ===\n");
	for (int d = 0; d < DIR_MAX; d++)
	{
		dir = (d == DIR_N) ? "NO" :
				(d == DIR_S) ? "SO" :
				(d == DIR_E) ? "EA" : "WE";
		printf("Texture %-2s: %s\n", dir,
			m->tex_paths[d] ? m->tex_paths[d] : "(null)");
	}
	print_color("Floor", m->floor_colr);
	print_color("Ceil ", m->ceil_colr);
	print_player(&m->player);
	print_grid(&m->g);
	printf("=============\n");
}
