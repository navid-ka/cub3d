/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:33:00 by bifrost           #+#    #+#             */
/*   Updated: 2024/03/21 22:51:38 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	map_lengh(t_game *g, t_map *map, t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
			j++;
		if (j > map->width)
			map->width = j;
		if (i > 0 && j != map->width)
		{
			printf("Error\nMap is not a square matrix.\n");
			fd_error_3(g, cub, map);
		}
		i++;
	}
	map->height = i;
}

int	orientation_char(char cub)
{
	if (cub == 'N' || cub == 'S' || cub == 'W' || cub == 'E')
		return (1);
	return (0);
}

int	around_zero(t_cub *cub, int index, char *line, int i)
{
	if (i >= (int)ft_strlen(cub->map[index + 1])
		|| cub->map[index + 1] == 0
		|| index - 1 < 0 || line[i - 1] == ' '
		|| line[i + 1] == ' ' || line[i + 1] == '\0'
		|| cub->map[index - 1][i] == ' '
		|| cub->map[index + 1][i] == '\0'
		|| cub->map[index + 1][i] == ' ')
	{
		return (1);
	}
	return (0);
}

int	around_pl(t_cub *cub, int i, int index)
{
	if (cub->map[index + 1] == 0
		|| index - 1 < 0
		|| cub->map[index][i - 1] == ' '
		|| cub->map[index][i + 1] == ' '
		|| cub->map[index][i + 1] == '\0'
		|| cub->map[index - 1][i] == ' '
		|| cub->map[index + 1][i] == '\0'
		|| cub->map[index + 1][i] == ' ')
	{
		return (0);
	}
	return (1);
}

int	check_possiblty(char c)
{
	if (c != ' ' && c != '1' && c != '2' && c != '3'
		&& c != '4' && c != 'D' && c != '0' && c != 'S'
		&& c != 'N' && c != 'E' && c != 'W')
		return (1);
	return (0);
}
