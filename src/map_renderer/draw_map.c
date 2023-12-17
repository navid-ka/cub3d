/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:00:44 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/17 12:07:51 by bifrost          ###   ########.fr       */
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
	g->img = malloc(sizeof(t_img) * (2 + 1));
	g->img[0].img = mlx_xpm_file_to_image(g->mlx_p, "textures/map/wall.xpm", &w, &h);
	g->img[1].img = mlx_xpm_file_to_image(g->mlx_p, "textures/map/path.xpm", &w, &h);
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

void draw_player(t_game *game)
{
    int tile_size = 32; // Assuming each tile is 32x32 pixels

    // Get the player's position in the map
    int player_row = (int)game->player_s->pos_y;
    int player_col = (int)game->player_s->pos_x;

    // Calculate the position to draw the player tile on the screen
    int x = player_col * tile_size;
    int y = player_row * tile_size;

    // Draw the player tile on the screen
//    printf("Player tile: %c\n", game->map_s->map[player_row][player_col]);
    mlx_put_image_to_window(game->mlx_s->mlx_p, game->mlx_s->win, game->mlx_s->img[0].img, x, y);
}