/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:00:44 by plinscho          #+#    #+#             */
/*   Updated: 2024/01/09 20:37:35 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

#define TILE_SIZE 1024


void get_image_addr(t_img *img)
{
    img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len, &img->endian);
}

void set_image_dimensions(t_img *img, int w, int h)
{
    img->width = w;
    img->height = h;
}

void sl_image_init(t_mlx *g)
{
    int h = 32;
    int w = 32;
    int w_w = 1280;
    int w_h = 720;
    int p_w = 128;
    int p_h = 128;


    g->img = malloc(sizeof(t_img) * (5 + 1));
    if (!g->img)
    {
        printf("Error\n[errno: %d] Malloc failed\n", errno);
        exit(0);
    }
    g->img[0].img = mlx_xpm_file_to_image(g->mlx_p, "textures/map/wall.xpm", &w, &h);
    g->img[0].addr = mlx_get_data_addr(g->img[0].img, &g->img[0].bpp, &g->img[0].line_len, &g->img[0].endian);
    g->img[0].width = w;
    g->img[0].height = h;
    g->img[0] = *resize_image(g, &g->img[0], 8, 8);
    
	printf("g->img[0].img = %p\n", g->img[0].img);
    g->img[1].img = mlx_xpm_file_to_image(g->mlx_p, "textures/map/path.xpm", &w, &h);
    g->img[1].addr = mlx_get_data_addr(g->img[1].img, &g->img[1].bpp, &g->img[1].line_len, &g->img[1].endian);
    g->img[1].width = w;
    g->img[1].height = h;
	printf("g->img[1].img = %p\n", g->img[1].img);
    g->img[2].img = mlx_xpm_file_to_image(g->mlx_p, "textures/map/clear.xpm", &w, &h);
    g->img[2].addr = mlx_get_data_addr(g->img[2].img, &g->img[2].bpp, &g->img[2].line_len, &g->img[2].endian);
    g->img[2].width = w;
    g->img[2].height = h;
	printf("g->img[2].img = %p\n", g->img[2].img);
    g->img[3].img = mlx_xpm_file_to_image(g->mlx_p, "textures/map/start.xpm", &w_w, &w_h);
    g->img[3].addr = mlx_get_data_addr(g->img[3].img, &g->img[3].bpp, &g->img[3].line_len, &g->img[3].endian);
    g->img[3].width = w_w;
    g->img[3].height = w_h;
	printf("g->img[3].img = %p\n", g->img[3].img);
    g->img[4].img = mlx_xpm_file_to_image(g->mlx_p, "textures/player/portrait.xpm", &p_w, &p_h);
    g->img[4].addr = mlx_get_data_addr(g->img[4].img, &g->img[4].bpp, &g->img[4].line_len, &g->img[4].endian);
    g->img[4].width = p_w;
    g->img[4].height = p_h;
	printf("g->img[4].img = %p\n", g->img[4].img);
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
    char    *pixel;

    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(int *)pixel = color;
}

t_img *create_new_img(t_mlx *g, int width, int height)
{
    t_img *new_img;

    new_img = malloc(sizeof(t_img));
    if (!new_img)
    {
        printf("Error\n[errno: %d] Malloc failed\n", errno);
        exit(0);
    }
    new_img->img = mlx_new_image(g->mlx_p, width, height);
    new_img->addr = mlx_get_data_addr(new_img->img, &new_img->bpp, &new_img->line_len, &new_img->endian);
    new_img->width = width;
    new_img->height = height;
    return (new_img);
}

unsigned int	get_pixel_img(t_img *img, int x, int y) 
{
    return (*(unsigned int *)((img->addr
            + (y * img->line_len) + (x * img->bpp / 8))));
}

t_img	*resize_image(t_mlx *g, t_img *img, int nw, int nh)
{
    t_position	od;
    t_img		*ri;
    int			c;
    t_position	p = {0, 0};
    t_position	op;

    od.x = img->height;
    od.y = img->width;
    ri = create_new_img(g, nw, nh);
    while (p.y < nh)
    {
        p.x = 0;
        while (p.x < nw)
        {
            op.x = p.x * od.x / nw;
            op.y = p.y * od.y / nh;
            c = ((int *)img->addr)[op.y * od.x + op.x];
            img_pix_put(ri, p.x, p.y, c);
            p.x++;
        }
        p.y++;
    }
    return (ri);
}

void draw_resized_img(t_mlx *g, t_img *img, int pos[2], int size[2])
{
    static t_img *resized_img;
	static int flag = 0;
	if (!flag)
	{
		resized_img = resize_image(g, img, size[0], size[1]);
		flag = 1;
	}
    mlx_put_image_to_window(g->mlx_p, g->win, resized_img->img, pos[0], pos[1]);
}

void	put_pixel_img(t_img *img, int x, int y, int color)
{
    char	*dst;

	if (color == (int)0xFF000000)
		return ;
    if (x >= 0 && y >= 0 && x < img->width && y < img->height) {
        dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
        *(unsigned int *) dst = color;
    }
}

void	put_img_to_img(t_img *dst, t_img *src, int x, int y) 
{
    int i;
    int j;

    i = 0;
    while(i < src->width) {
        j = 0;
        while (j < src->height) {
            put_pixel_img(dst, x + i, y + j, get_pixel_img(src, i, j));
            j++;
        }
        i++;
    }
}

/*
t_img *double_bpp_image(t_mlx *g, t_img *img, int width, int height)
{
	t_img *doubled_img = malloc(sizeof(t_img));
	doubled_img->img = mlx_new_image(g->mlx_p, width, height);
	doubled_img->addr = mlx_get_data_addr(doubled_img->img, &doubled_img->bpp, &doubled_img->line_length, &doubled_img->endian);
	int x = 0;
	int y = 0;
	int color;
	while (y < height)
	{
		while (x < width)
		{
			color = ((int *)img->addr)[(y * img->line_length + x * (img->bpp / 8)) / 4];
			img_pix_put(doubled_img, x, y, color);
			x++;
		}
		x = 0;
		y++;
	}
	return doubled_img;
}


void draw_doubled_image(t_mlx *g, t_img *img, int pos_x, int pos_y)
{
	t_img *doubled_img = double_bpp_image(g, img, 64, 64);

	mlx_put_image_to_window(g->mlx_p, g->win, doubled_img->img, pos_x, pos_y);
}*/
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