/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 23:33:36 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/06 00:05:05 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
 #define RAYCAST_H

#define PI 3.1415926535
#include <math.h>

typedef struct s_player
{
    double  x; //position
    double  y;
    double  fov;
}t_player;

void    ft_cast_rays(t_player *p1, char **map);

#endif