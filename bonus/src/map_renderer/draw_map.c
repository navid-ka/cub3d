/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:00:44 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/28 17:56:07 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

#define TILE_SIZE 1024

void	sl_image_init(t_mlx *g)
{
	int h;
	int w;
	
	h = 32;
	w = 32;
	int w_w = 1280;
	int w_h = 720;
	g->img = malloc(sizeof(t_img) * (4 + 1));
	if (!g->img)
	{
		printf("Error\n[errno: %d] Malloc failed\n", errno);
		exit(0);
	}
	g->img[0].img = mlx_xpm_file_to_image(g->mlx_p, "textures/map/wall.xpm", &w, &h);
	g->img[1].img = mlx_xpm_file_to_image(g->mlx_p, "textures/map/path.xpm", &w, &h);
	g->img[2].img = mlx_xpm_file_to_image(g->mlx_p, "textures/map/clear.xpm", &w, &h);
	g->img[3].img = mlx_xpm_file_to_image(g->mlx_p, "textures/map/start.xpm", &w_w, &w_h);
}
/*
static void print_map(t_game *game)
{
	for (int row = 0; row < game->map_s->height; row++)
	{
		for (int col = 0; col < game->map_s->width; col++)
		{
			printf("%c", game->map_s->map[row][col]);
		}
		printf("\n");
	}
}
*/

void clear_player(t_game *game)
{
	//old player position
	int y = (int)game->player_s->pos_y * 32;
	int x = (int)game->player_s->pos_x * 32;
	mlx_put_image_to_window(game->mlx_s->mlx_p, game->mlx_s->win, game->mlx_s->img[2].img, x, y);
	
}

void draw_player(t_game *game)
{
    // Get the player's position in the map
	int y = (int)game->player_s->pos_y * 32;
	int x = (int)game->player_s->pos_x * 32;

    // Draw the player tile on the screen
//    printf("Player tile: %c\n", game->map_s->map[player_row][player_col]);
    mlx_put_image_to_window(game->mlx_s->mlx_p, game->mlx_s->win, game->mlx_s->img[0].img, x, y);
}