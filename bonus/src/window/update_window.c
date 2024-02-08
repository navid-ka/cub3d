/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:48:19 by bifrost           #+#    #+#             */
/*   Updated: 2024/02/08 10:29:04 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int update(t_game *game) 
{
    char *str;

    str = NULL;
    if (timestamp_in_ms(game) - game->updated_at < (uint64_t)(1000 / game->fps))
        return 0;
    game->updated_at = timestamp_in_ms(game);
    game->frame_count++;
    //printf("frame: %llu\n", game->frame_count);
    if (game->state == GAME)
    {
        raycast(game);
        draw_minimap(game);
        if (game->player_s->door_collision == true)
			draw_str_to_font(game->mlx_s, "Press E to open door", S_HEIGHT /2, S_WIDTH / 2);
    }
    put_img_to_img(game->mlx_s->buffer, &game->mlx_s->img[4], 20, 20);
    if (game->state == COMBAT)
    {
        paint_mid_wall(game);
        put_img_to_img(game->mlx_s->buffer, &game->mlx_s->img[4], 20, 20);
        combat_manager(game);
    }
    game->sword_state = sword_manager(game, game->sword_state);
    str = ft_itoa(game->player_s->hp);
    draw_str_to_font(game->mlx_s, str, 20, 150);
    free(str);
    //put_img_to_img(game->mlx_s->buffer, &game->mlx_s->fonts[0], 20, 70);
    mlx_put_image_to_window(game->mlx_s->mlx_p, game->mlx_s->win, game->mlx_s->buffer->img, 0, 0);
    return 0;
}
