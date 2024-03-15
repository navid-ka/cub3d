/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:47:35 by bifrost           #+#    #+#             */
/*   Updated: 2024/03/15 18:55:22 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_map(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (cub->map[++i])
	{
		j = -1;
		while (cub->map[i][++j])
		{
			if (orientation_char(cub->map[i][j]))
			{
				if (!around_pl(cub, j, i))
					return (0);
			}
			else if (cub->map[i][j] == '0')
			{
				if (around_zero(cub, i, cub->map[i], j))
					return (0);
			}
			else if (check_possiblty(cub->map[i][j]))
				return (0);
		}
	}
	return (1);
}

int	map_valid_orientation(t_cub *cub, t_map *map)
{
	int	i;
	int	j;

	i = ~0;
	while (cub->map[++i])
	{
		j = ~0;
		while (cub->map[i][++j])
		{
			if (orientation_char(cub->map[i][j]))
			{
				if (cub->map[i][j] == 'N')
					map->orientation = 270;
				else if (cub->map[i][j] == 'S')
					map->orientation = 90;
				else if (cub->map[i][j] == 'W')
					map->orientation = 0;
				else if (cub->map[i][j] == 'E')
					map->orientation = 180;
				return (1);
			}
		}
	}
	return (0);
}

int	map_has_valid_char(t_cub *cub)
{
	char	*valid_chars;
	int		j;
	int		i;

	valid_chars = "01234DNSEW ";
	i = 0;
	cub->count = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (orientation_char(cub->map[i][j]))
				cub->count++;
			if (ft_strchr(valid_chars, cub->map[i][j]) == NULL)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	map_get_player_pos(t_map *map, t_player *player)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (orientation_char(map->map[i][j]))
			{
				player->pos_x = j;
				player->pos_y = i;
			}
			j++;
		}
		i++;
	}
}

void	map_parser(t_game *game, t_cub *cub, t_map *map)
{
	int			is_valid;
	t_player	*player;

	player = game->player_s;
	map_lengh(map);
	map_get_player_pos(map, player);
	is_valid = map_has_valid_char(cub)
		&& map_valid_orientation(cub, map)
		&& check_map(cub) && cub->count == 1;
	if (!is_valid)
	{
		printf("Error\nMap did not meet requirements.\n");
		fd_error_3(game, cub, map);
	}
}
