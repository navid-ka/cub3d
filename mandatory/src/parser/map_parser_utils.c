/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:41:28 by plinscho          #+#    #+#             */
/*   Updated: 2024/02/23 17:44:41 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_possiblty(char c)
{
	if (c != ' ' && c != '1' && c != '0' && c != 'S'
		&& c != 'N' && c != 'E' && c != 'W')
		return (1);
	return (0);
}

void	print_flood(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			printf("%c", cub->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	map_lengh(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->map[i])
	{
		while (map->map[i][j])
			j++;
		if (j > map->width)
			map->width = j;
		j = 0;
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
	if (i >= (int)ft_strlen(cub->map[index + 1]) || \
		cub->map[index + 1] == 0 || \
		index - 1 < 0 || line[i - 1] == ' ' || \
		line[i + 1] == ' ' || line[i + 1] == '\0' || \
		cub->map[index - 1][i] == ' ' || \
		cub->map[index + 1][i] == '\0' || \
		cub->map[index + 1][i] == ' ')
	{
		return (1);
	}
	return (0);
}
