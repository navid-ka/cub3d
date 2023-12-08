/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:47:35 by bifrost           #+#    #+#             */
/*   Updated: 2023/12/08 13:51:07 by bifrost          ###   ########.fr       */
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

int map_check_walls(t_cub *cub) //TODO: check if map is surrounded by walls NOT WORKING
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
                if (cub->map[i][j + 1] == ' ' || cub->map[i][j - 1] == ' '
                    || cub->map[i + 1][j] == ' ' || cub->map[i - 1][j] == ' ')
                    return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}
void map_get_player_pos(t_map *map)
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
                    map->pos_x = j;
                    map->pos_y = i;
            }
            j++;
        }
        i++;
    }    
}

void map_parser(t_cub *cub, t_map *map)
{
    int is_valid;

    map_lengh(map);
    is_valid = map_has_valid_char(cub)
        && map_valid_orientation(cub, map) 
        && map_check_walls(cub);
    if (!is_valid)
        printf("Error\nMap did not meet requirements.\n");\
    map_get_player_pos(map);
    printf("player pos x: [%d]\n", map->pos_x);
    printf("player pos y: [%d]\n", map->pos_y);
    printf("map orientation: [%d]\n", map->orientation);
}