/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:03:10 by plinscho          #+#    #+#             */
/*   Updated: 2024/03/21 19:21:46 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

double	deg_to_rad(int dg_angle)
{
	return (dg_angle * PI / 180);
}

int	rad_to_dg(double angle)
{
	return ((int)(angle * 180 / PI));
}

double	plane_mult(int fov)
{
	double	plane_multiplier;

	plane_multiplier = deg_to_rad(fov);
	plane_multiplier = tan(plane_multiplier / 2);
	plane_multiplier = 2 / plane_multiplier;
	return (plane_multiplier);
}
