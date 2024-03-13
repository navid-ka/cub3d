/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:09:19 by bifrost           #+#    #+#             */
/*   Updated: 2024/03/13 12:20:01 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

double	apply_fog(t_game *game)
{
	double	brightness;

	brightness = 1.0 - (game->camera_s->perp_wall_dist / 10);
	if (brightness < 0)
		brightness = 0;
	if (game->camera_s->side == 1)
		brightness *= 0.8;
	return (brightness);
}
