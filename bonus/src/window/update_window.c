/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:48:19 by bifrost           #+#    #+#             */
/*   Updated: 2024/01/11 20:49:06 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int update(t_game *game) 
{
    if (timestamp_in_ms(game) - game->updated_at < (uint64_t)(1000 / game->fps))
        return 0;
    game->updated_at = timestamp_in_ms(game);
    
    draw_minimap(game);
    put_img_to_img(game->mlx_s->buffer, &game->mlx_s->img[4], 20, 20);
    if (game->state == COMBAT)
    {
        put_img_to_img(game->mlx_s->buffer, &game->mlx_s->enemy[1], (game->mlx_s->screen_width - game->mlx_s->enemy[1].width) / 2, (game->mlx_s->screen_height - game->mlx_s->enemy[1].height) / 2);
        combat_manager(game);
    }
    game->sword_state = sword_manager(game, game->sword_state);
    mlx_put_image_to_window(game->mlx_s->mlx_p, game->mlx_s->win, game->mlx_s->buffer->img, 0, 0);
    return 0;
}
