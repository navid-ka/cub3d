/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:35:01 by bifrost           #+#    #+#             */
/*   Updated: 2024/02/13 13:36:12 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	collision_checker(t_game *game, double dx, double dy)
{
	static double	margin = 0.07;
	char			*wall;

	wall = "1234D";
	if (game->door_state == OPEN)
		wall = "1234";
	check_collision_x(game, dx, wall, margin);
	check_collision_y(game, dy, wall, margin);
	return (0);
}
