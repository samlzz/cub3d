#include <stdint.h>
#include <stdio.h>

#include "color.h"
#include "cubmap.h"

static void	print_color(const char *label, const t_color *c)
{
	if (!c)
		printf("%s: (null)\n", label);
	else
		printf("%s: R=%u G=%u B=%u\n", label, c->code.r, c->code.g, c->code.b);
}

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
	for (int d = 0; d < TEX__COUNT; d++)
	{
		dir = (d == TEX_N) ? "NO" :
				(d == TEX_S) ? "SO" :
				(d == TEX_E) ? "EA" :
				(d == TEX_W) ? "WE" : "DOOR";
		printf("Texture %-2s: %s\n", dir, m->textures[d].path);
	}
	print_color("Floor", &m->floor_colr);
	print_color("Ceil ", &m->ceil_colr);
	print_grid(&m->g);
	printf("=============\n");
}

