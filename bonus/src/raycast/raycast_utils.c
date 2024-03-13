/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 23:33:30 by plinscho          #+#    #+#             */
/*   Updated: 2024/03/13 12:28:23 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

double	plane_mult(int fov)
{
	double	plane_multiplier;

	plane_multiplier = deg_to_rad(fov);
	plane_multiplier = tan(plane_multiplier / 2);
	plane_multiplier = 2 / plane_multiplier;
	return (plane_multiplier);
}

double	deg_to_rad(int dg_angle)
{
	return (dg_angle * PI / 180);
}

int	rad_to_dg(double angle)
{
	return ((int)(angle * 180 / PI));
}
