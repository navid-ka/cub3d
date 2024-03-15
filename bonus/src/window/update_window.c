/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:48:19 by bifrost           #+#    #+#             */
/*   Updated: 2024/03/15 17:54:58 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_player_hp(t_game *game)
{
	char	*str;

	str = ft_itoa(game->player_s->hp);
	draw_str_to_font(game->mlx_s, "HP:", 20, 150);
	draw_str_to_font(game->mlx_s, str, 60, 150);
	free(str);
}

int	update(t_game *game)
{
	if (timestamp_in_ms(game) - game->updated_at < (uint64_t)(1000 / game->fps))
		return (0);
	game->updated_at = timestamp_in_ms(game);
	game->frame_count++;
	if (game->state == GAME)
	{
		raycast(game);
		draw_minimap(game);
		if (game->player_s->door_collision == true)
			draw_str_to_font(game->mlx_s, "Press E to open door",
				S_HEIGHT / 2, S_WIDTH / 2);
	}
	put_img_to_img(game->mlx_s->buffer, &game->mlx_s->img[4], 20, 20);
	if (game->state == COMBAT)
	{
		paint_mid_wall(game);
		put_img_to_img(game->mlx_s->buffer, &game->mlx_s->img[4], 20, 20);
		combat_manager(game);
	}
	game->sword_state = sword_manager(game, game->sword_state);
	draw_player_hp(game);
	mlx_put_image_to_window(game->mlx_s->mlx_p, game->mlx_s->win,
		game->mlx_s->buffer->img, 0, 0);
	look_with_mouse(game);
	return (0);
}
