#include <stdint.h>
#include <stdio.h>

#include "libft.h"
#include "cubmap.h"
#include "error.h"
#include "parsing/parser.h"
#include "test.h"

int main(int ac, char **av)
{
	int16_t	code;
	t_map	map;
	char	**tmp;
	char	**n;

	if (ac != 2 || !is_dot_cub(av[1]))
		return (ft_putendl_fd(ERR_WRONG_USAGE, 2), 2);
	ft_bzero(&map, sizeof(t_map));
	code = parse_cub(av[1], &map);
	if (code)
		return (free_map(&map), code);
	print_map(&map);
	n = get_normalized_grid(&map);
	tmp = map.grid;
	map.grid = n;
	printf("### NORMALIZED: ###\n\n");
	print_map(&map);
	ft_splitfree(n, map.dimensions.y + 2);
	map.grid = tmp;
	free_map(&map);
	return (0);
}