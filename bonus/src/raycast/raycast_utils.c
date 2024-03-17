/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 23:33:30 by plinscho          #+#    #+#             */
/*   Updated: 2024/03/17 16:21:09 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

double	plane_mult(double fov)
{
	double	plane_multiplier;

	plane_multiplier = fov;
	plane_multiplier = tan(plane_multiplier / 2);
	plane_multiplier = 2 / plane_multiplier;
	return (plane_multiplier);
}

double	deg_to_rad(double dg_angle)
{
	return (dg_angle * PI / 180);
}

int	rad_to_dg(double angle)
{
	return ((int)(angle * 180 / PI));
}
