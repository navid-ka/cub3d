/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 23:33:30 by plinscho          #+#    #+#             */
/*   Updated: 2024/01/06 18:00:05 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

double	deg_to_rad(int dg_angle)
{
	return (dg_angle * PI / 180);
}

int		rad_to_dg(double angle)
{
	return ((int)(angle * 180 / PI));
}
