/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:48:19 by bifrost           #+#    #+#             */
/*   Updated: 2024/01/27 22:20:27 by bifrost          ###   ########.fr       */
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
    
    raycast(game);
    draw_minimap(game);
    put_img_to_img(game->mlx_s->buffer, &game->mlx_s->img[4], 20, 20);
    if (game->state == COMBAT)
    {
        //enemy_type(game, game->random);
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
