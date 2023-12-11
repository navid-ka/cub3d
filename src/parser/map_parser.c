/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- <nkeyani-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:47:35 by bifrost           #+#    #+#             */
/*   Updated: 2023/12/11 18:47:14 by nkeyani-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void   map_lengh(t_map *map)
{
	int i;
	int j;

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

int map_check_len(t_cub *cub)
{
	size_t	len;
	int		i;

	i = 0;
	len = ft_strlen(cub->map[i]);
	i++;
	while (cub->map[i] != NULL)
	{
		if (len != ft_strlen(cub->map[i]))
			return (0);
		printf("len and strlen: %zu %zu\n", len, ft_strlen(cub->map[i]));
		i++;
	}
	return (1);
}

int map_valid_orientation(t_cub *cub, t_map *map)
{
	int i;
	int j;

	i = ~0;
	while (cub->map[++i])
	{
		j = ~0;
		while (cub->map[i][++j])
		{
			if (cub->map[i][j] == 'N' || cub->map[i][j] == 'S' 
				|| cub->map[i][j] == 'W' || cub->map[i][j] == 'E')
			{
				if (cub->map[i][j] == 'N')
					map->orientation = 90;
				else if (cub->map[i][j] == 'S')
					map->orientation = 270;
				else if (cub->map[i][j] == 'W')
					map->orientation = 180;
				else if (cub->map[i][j] == 'E')
					map->orientation = 0;
				return (1);
			}
		}
	}
	return (0);
}

int map_has_valid_char(t_cub *cub)
{
	char    *valid_chars;
	int     j;
	int     i;

	valid_chars = "01NSEW ";
	i = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (ft_strchr(valid_chars, cub->map[i][j]) == NULL)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int map_get_begining(t_cub *cub)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (cub->map[i])
	{
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == '1')
			{
				cub->begin[0] = i;
				cub->begin[1] = j;
				return (1);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int    map_flood(t_game *g, int i, int j)
{
	int height;
	int width;

	height = g->map_s->height;
	width = g->map_s->width;
	if (i < 0 || j < 0 || i >= height || j >= width)
        return (0);
	while (g->cub_s->map[i][j]
			&& g->cub_s->map[i][j] != '0'
			&& g->cub_s->map[i][j] != ' '
			&& g->cub_s->map[i][j] != 'X')
	{
		g->cub_s->map[i][j] = 'X';
		map_flood(g, i + 1, j);
		map_flood(g, i - 1, j);
		map_flood(g, i, j + 1);
		map_flood(g, i, j - 1);
	}
	return (1);
}

int map_check_walls(t_cub *cub, t_game *g) 
{
	int i;
	int j;

	i = -1;

	if (map_get_begining(cub) == 0)
		printf("Error\nMap not valid\n");
	printf("map begining: [%d, %d]\n", cub->begin[0], cub->begin[1]);
	if (map_flood(g, cub->begin[0], cub->begin[1]) == 0)
		printf("Error\nMap not valid\n");
	printf("map flood good\n");
	while (g->cub_s->map[++i])
	{
		j = -1;
		while (g->cub_s->map[i][++j])
			if (g->cub_s->map[i][j] 
			&& g->cub_s->map[i][j] == '0' 
			&& (g->cub_s->map[i + 1][j] == ' '
					|| g->cub_s->map[i - 1][j] == ' ' 
					|| g->cub_s->map[i][j + 1] == ' '
					|| g->cub_s->map[i][j - 1] == ' ')) 
					{
						printf("Error\nMap not valid while\n");
						return (0);}
	}
	printf("map flood\n");
	while (*cub->map)
	{
		printf("%s\n", *cub->map);
		cub->map++;
	}
	return (1);
}



void map_get_player_pos(t_map *map, t_player *player)
{
	int i;
	int j;
	
	i = 0;
	while(map->map[i])
	{
		j = 0;
		while(map->map[i][j])
		{
			if(map->map[i][j] == 'N' || map->map[i][j] == 'S' 
				|| map->map[i][j] == 'W' || map->map[i][j] == 'E')
			{
					player->pos_x = j;
					player->pos_y = i;
			}
			j++;
		}
		i++;
	}
}

void map_parser(t_game *game, t_cub *cub, t_map *map)
{
	int         is_valid;
	t_player    *player;

	player = game->player_s;
	map_lengh(map);
	map_get_player_pos(map, game->player_s);
	is_valid = map_has_valid_char(cub)
		&& map_valid_orientation(cub, map)
		&& map_check_walls(cub, game);
	if (!is_valid)
	{
		printf("Error\nMap did not meet requirements.\n");
		exit (1);
	}
	/*if (map_check_len(cub) == 0)
	{
		printf("Error\nMap len not valid\n"); ESTO NOO VAAAAAA
	}*/
	printf("player pos x: [%f]\n", player->pos_x);
	printf("player pos y: [%f]\n", player->pos_y);
	printf("map orientation: [%d]\n", map->orientation);
}