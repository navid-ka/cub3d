/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 23:33:34 by plinscho          #+#    #+#             */
/*   Updated: 2024/02/08 18:49:12 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	char_to_int(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
{
    return (*(int *)(unsigned char [4]){b, g, r, t});
}

int	get_pixel_color(t_img *img, int x, int y, double brightness)
{
    char	*addr;
    int		color;

    // Comprueba si las coordenadas están dentro de los límites de la imagen
	color = 0;
    if (x < 0 || x >= img->width || y < 0 || y >= img->height)
        return (0);
    addr = img->addr + (y * img->line_len + x * (img->bpp / 8));
    color = char_to_int(addr[3] * brightness, addr[2] * brightness, addr[1] * brightness, addr[0] * brightness);
    return (color);
}

int	colors(t_color *c)
{
	return (c->r << 16 | c->g << 8 | c->b);
}

// This function sets the camera position and direction
void	init_ray(t_player *p, t_camera *c, int i)
{
	double	fov_scale;
	
	// the ray direction is the player direction + the camera plane
	
	fov_scale = p->fov/PI;
	c->camera_x = 2 * fov_scale * (i/(double)S_WIDTH) - fov_scale;	// x-coordinate in camera space
	c->ray_dir_x = p->dir_x + c->plane_x * c->camera_x;
	c->ray_dir_y = p->dir_y + c->plane_y * c->camera_x;
	
	c->map_x = (int)p->pos_x;
	c->map_y = (int)p->pos_y;
	
	// distance the ray has to travel to go from 1 x-side to the next x-side
	if (c->ray_dir_x == 0)
		c->delta_dist_x = 1e30;
	else
		c->delta_dist_x = fabsl(1 / c->ray_dir_x);

	if (c->ray_dir_y == 0)
		c->delta_dist_y = 1e30;
	else
		c->delta_dist_y = fabsl(1 / c->ray_dir_y);
}

// what direction to step in x or y-direction (either +1 or -1)
// Basically, if angle is bigger than 180, the ray is pointing left, so we need to step in the negative x-direction
// If the angle is smaller than 180, the ray is pointing right, so we need to step in the positive x-direction
// Same logic for the y-direction
void	init_step(t_player *p, t_camera *c)
{
	if (c->ray_dir_x < 0)	// if the ray is pointing left
	{
		c->step_x = -1;	// step in the negative x-direction
		c->side_dist_x = (p->pos_x - c->map_x) * c->delta_dist_x;	// calculate the distance to the next x-side
	}
	else
	{
		c->step_x = 1;	// step in the positive x-direction
		c->side_dist_x = (c->map_x + 1.0 - p->pos_x) * c->delta_dist_x;	// calculate the distance to the next x-side
	}
	if (c->ray_dir_y < 0)	// if the ray is pointing up
	{
		c->step_y = -1;
		c->side_dist_y = (p->pos_y - c->map_y) * c->delta_dist_y;
	}
	else					// if the ray is pointing down
	{
		c->step_y = 1;	
		c->side_dist_y = (c->map_y + 1.0 - p->pos_y) * c->delta_dist_y;
	}
}

static void	dda_aux(t_camera *c)
{
	if (c->side == 0)
	{
		if (c->step_x > 0)
			c->hit_direction = SOUTH;
		else
			c->hit_direction = NORTH;
	}
	else
	{
		if (c->step_y > 0)
			c->hit_direction = EAST;
		else
			c->hit_direction = WEST;
	}
}


void	init_dda(t_line *line, t_player *p, t_camera *c, char **map)
{
    c->hit = 0;
    line->color_fader = 0;
    while (c->hit == 0)
    {
        if (c->side_dist_x < c->side_dist_y)	// if the next x-side is closer than the next y-side
        {
            c->side_dist_x += c->delta_dist_x;	
            c->map_x += c->step_x;				// move to the next x-side
            c->side = 0;						// set the side to 0 (NS)
        }
        else
        {
            c->side_dist_y += c->delta_dist_y;
            c->map_y += c->step_y;
            c->side = 1;						// set the side to 1 (EW)
        }
        if (map[c->map_y][c->map_x] == '1' || map[c->map_y][c->map_x] == '2' 
			|| map[c->map_y][c->map_x] == '3' || map[c->map_y][c->map_x] == '4'
			|| map[c->map_y][c->map_x] == 'D')
        {
            c->hit = 1;
			c->type = map[c->map_y][c->map_x];
            dda_aux(c);
        }
        line->color_fader += 0;
    }
    // Calculations avoiding "fish eye" effect NOTE: I don't understand this part
    if (c->side == 0)	// if the NS side was hit
        c->perp_wall_dist = (c->map_x - p->pos_x + (1 - c->step_x) / 2) / c->ray_dir_x;	// calculate the distance to the point of impact
    else
        c->perp_wall_dist = (c->map_y - p->pos_y + (1 - c->step_y) / 2) / c->ray_dir_y;

    // Calculate wall_x
    if (c->side == 0)
        c->wall_x = p->pos_y + c->perp_wall_dist * c->ray_dir_y;
    else
        c->wall_x = p->pos_x + c->perp_wall_dist * c->ray_dir_x;
    c->wall_x -= floor((c->wall_x));
}

/*
	if (c->side == 0)	// if the NS side was hit
		c->perp_wall_dist = (c->map_x - p->pos_x + (1 - c->step_x) / 2) / c->ray_dir_x;	// calculate the distance to the point of impact
	else
		c->perp_wall_dist = (c->map_y - p->pos_y + (1 - c->step_y) / 2) / c->ray_dir_y;
*/
void	init_line(t_line *line, t_camera *c, int i)
{
	// Calculate the height of the line
	line->line_height = (int)(S_HEIGHT / c->perp_wall_dist) * 2;
	
	// Calculate the lowest and highest pixel to fill in current stripe
	line->draw_start = -line->line_height / 2 + S_HEIGHT / 2;
	if (line->draw_start < 0)
		line->draw_start = 0;
	line->draw_end = line->line_height / 2 + S_HEIGHT / 2;
	if (line->draw_end >= S_HEIGHT)
		line->draw_end = S_HEIGHT - 1;

	// Calculate the color of the line
	line->x_start = i;
	line->x_end = i;
	// color depends on the distance to the wall
	line->color = 0xFF0F00;
}

void draw_ceil(t_game *game, t_img *img, t_line *line, int *i)
{
    while (*i < (S_HEIGHT / 2 - line->line_height / 2))
        img_pix_put(img, line->x_start, (*i)++, colors(&game->cub_s->ceiling));
}

void draw_floor(t_game *game, t_img *img, t_line *line, int *i)
{
    while (*i < S_HEIGHT)
        img_pix_put(img, line->x_start, (*i)++, colors(&game->cub_s->floor));
}

double apply_fog(t_game *game)
{
    double brightness;
	
	brightness = 1.0 - (game->camera_s->perp_wall_dist / 10);
    if (brightness < 0)
        brightness = 0;
    if (game->camera_s->side == 1)
        brightness *= 0.8;

    return (brightness);
}

void calculate_line_properties(t_game *game, t_line *line, t_img *img, t_img *source_img)
{
    line->text_x = (int)(game->camera_s->wall_x * (double)(source_img->width));
    if(game->camera_s->side == 0 && game->camera_s->ray_dir_x > 0) 
        line->text_x = source_img->width - line->text_x - 1;
    if(game->camera_s->side == 1 && game->camera_s->ray_dir_y < 0) 
        line->text_x = source_img->width - line->text_x - 1;
    line->step = 1.0 * source_img->height / line->line_height;
    line->text_pos = (line->draw_start - img->height / 2 + (line->line_height) / 2) * line->step;
}

void draw_line(t_game *game, t_line *line, int w,  t_img *img, t_img *source_img)
{
    int i;

	calculate_line_properties(game, line, img, source_img);
    line->brightness = apply_fog(game);
    i = 0;
    draw_ceil(game, img, line, &i);
    while (i < S_HEIGHT && i < (S_HEIGHT / 2 + line->line_height / 2))
    {
        line->text_y = (int)line->text_pos & (source_img->height - 1);
        line->text_pos += line->step;
        if (line->text_y <= 62)
        {
            line->offset = w;
            if (line->offset >= 0 && line->offset < img->width)
            {
                img_pix_put(img, line->offset, i, get_pixel_color(source_img, line->text_x, line->text_y, line->brightness));
            }
        }
        i++;
    }
    draw_floor(game, img, line, &i);
}


void	draw(t_game *g, t_camera *cub, int w, t_img *image, t_line *line)
{
    if (cub->type == '1')
        draw_line(g, line, w, image, &g->mlx_s->wall[0]);
    else if (cub->type == '2')
        draw_line(g, line, w, image, &g->mlx_s->wall[1]);
    else if (cub->type == '3')
        draw_line(g, line, w, image, &g->mlx_s->wall[2]);
    else if (cub->type == '4')
        draw_line(g, line, w, image, &g->mlx_s->wall[3]);
    else if (cub->type == 'D')
    {
		/*if (g->door_state == OPEN)
		{
			cub->hit = 0;
			// Dibuja la puerta completamente abierta
			//draw_line(g, line, w + (DOOR_MAX_DISTANCE -3), image, &g->mlx_s->wall[5]);
			//draw_line(g, line, w - (DOOR_MAX_DISTANCE -3), image, &g->mlx_s->wall[6]);
		}
		else if (g->door_state == OPENING || g->door_state == CLOSING)
		{
			// Dibuja la puerta en proceso de abrirse o cerrarse
			cub->hit = 0;
			//draw_line(g, line, w + g->door_offset, image, &g->mlx_s->wall[4]);
            //draw_line(g, line, w - g->door_offset / 2, image, &g->mlx_s->wall[5]);
            //draw_line(g, line, w + g->door_offset / 2, image, &g->mlx_s->wall[6]);
		}
		else */if (g->door_state == CLOSED)
		{
			// Dibuja la puerta completamente cerrada
			draw_line(g, line, w, image, &g->mlx_s->wall[4]);
		}
    }
}

void raycast(t_game *game)
{
    t_line line;
    int i;
    t_img img;

    i = 0;
    img = create_new_img(game->mlx_s, 1280, 720);
    while (i < S_WIDTH)
    {
        // 1. Get player position and get the structs needed for the raycasting
        init_ray(game->player_s, game->camera_s, i); // Gets the position from player and sets the direction vector
        init_step(game->player_s, game->camera_s); // Sets the step and the side distance
        init_dda(&line, game->player_s, game->camera_s, game->map_s->map); // Performs the DDA algorithm
        // 2. Get the height of the wall
        init_line(&line, game->camera_s, i);
        draw(game, game->camera_s, i, &img, &line); // Pasamos la dirección de img
        i++;
    }
    put_img_to_img(game->mlx_s->buffer, &img, 0, 0); // Pasamos la dirección de img
    mlx_destroy_image(game->mlx_s->mlx_p, img.img); // Accedemos directamente a img.img
}

/*
// PSEUDOCODE
void	raycast(t_game *g)
{
	// 1. get the player position and direction, using cos and sin
	
	// 2. get the angle of the first ray, using the fov and the player direction
	// 3. for each ray, do the following:
	// 3.1. get the first intersection with a wall
	// 3.2. get the distance to the wall
	// 3.3. get the height of the wall
	// 3.4. get the color of the wall
	// 3.5. draw the wall
	// 4. draw the minimap
}

*/