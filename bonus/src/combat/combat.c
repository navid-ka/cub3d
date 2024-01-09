/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 04:01:07 by bifrost           #+#    #+#             */
/*   Updated: 2024/01/09 04:22:23 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

unsigned int f_randi(uint32_t idx)
{
	idx = (idx << 13) ^ idx;
	return ((idx * (idx * idx * 15731 + 789221) + 1376312589) & 0x7fffffff);
}

int combat(t_game *g)
{
    (void)g;
    printf("entered combat\n");
    return (COMBAT);
}