/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:47:35 by bifrost           #+#    #+#             */
/*   Updated: 2023/12/12 02:45:19 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void print_flood(t_cub *cub)
{
	int i;
	int j;

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
        if (cub->map[i] && len != ft_strlen(cub->map[i]))
            return (0);
        printf("len and strlen: %zu %zu\n", len, ft_strlen(cub->map[i]));
        i++;
    }
    return (1);
}
int orientation_char(char cub)
{
	if (cub == 'N' || cub == 'S' || cub == 'W' || cub == 'E')
		return (1);
	return (0);
}

int around_zero(t_cub *cub, int index, char *line, int i)
{
    if (i >= (int)ft_strlen(cub->map[index + 1]) ||
        cub->map[index + 1] == 0 ||
        index - 1 < 0 || line[i - 1] == ' ' ||
        line[i + 1] == ' ' || line[i + 1] == '\0' ||
        cub->map[index - 1][i] == ' ' ||
        cub->map[index + 1][i] == '\0' ||
        cub->map[index + 1][i] == ' ')
    {
        return (1);
    }
    return (0);
}

int around_ps(t_cub *cub, int i, int index)
{
    if (cub->map[index + 1] == 0 ||
        index - 1 < 0 ||
        cub->map[index][i - 1] == ' ' ||
        cub->map[index][i + 1] == ' ' ||
        cub->map[index][i + 1] == '\0' ||
        cub->map[index - 1][i] == ' ' ||
        cub->map[index + 1][i] == '\0' ||
        cub->map[index + 1][i] == ' ')
    {
        return 0;
    }
    return 1;
}
int	check_possiblty(char c)
{
	if (c != ' ' && c != '1' && c != '0' && c != 'S'
		&& c != 'N' && c != 'E' && c != 'W')
		return (1);
	return (0);
}

int check_map(t_cub *cub)
{
    int i;
	int j;

    i = 0;
    while (cub->map[i])
    {
        j = 0;
        while (cub->map[i][j])
        {
            if (orientation_char(cub->map[i][j]))
            	around_ps(cub, j, i);
            else if (cub->map[i][j] == '0')
			{
                if (around_zero(cub, i, cub->map[i], j))
                    return (0);
			}
			else if (check_possiblty(cub->map[i][j]))
				return (0);
            j++;
        }
        i++;
    }
    return 1;
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
			if (orientation_char(cub->map[i][j]))
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

void map_dfs(t_game *g, int i, int j)
{
    int height = g->map_s->height;
    int width = g->map_s->width;

    if (i < 0 || j < 0 || i >= height || j >= width
		|| g->cub_s->map[i][j] == '\0'
        || g->cub_s->map[i][j] == 'X'
		|| g->cub_s->map[i][j] == ' ' 
		)
        return ;
    g->cub_s->map[i][j] = 'X';
    map_dfs(g, i + 1, j);
    map_dfs(g, i - 1, j);
    map_dfs(g, i, j + 1);
    map_dfs(g, i, j - 1);
}

int check_visited(t_cub *cub)
{
    int i = 0;
    int j;

    while (cub->map[i])
    {
        j = 0;
        while (cub->map[i][j])
        {
            if (cub->map[i][j] != ' ' && cub->map[i][j] != 'X')
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}

int map_check_dfs(t_cub *cub, t_game *g)
{
    int i;
    int j;
    int result;

    i = 0;
    while (cub->map[i])
    {
        j = 0;
        while (cub->map[i][j])
        {
            map_dfs(g, i, j);
            result = check_visited(cub);
            return (result);
        }
        	j++;
        
        i++;
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
			if(orientation_char(map->map[i][j]))
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
		&& check_map(cub) && cub->count == 1;
	if (!is_valid)
	{
		printf("Error\nMap did not meet requirements.\n");
		exit (1);
	}
	print_flood(cub);
	printf("player pos x: [%f]\n", player->pos_x);
	printf("player pos y: [%f]\n", player->pos_y);
	printf("map orientation: [%d]\n", map->orientation);
}