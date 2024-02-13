/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_rands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:12:29 by bifrost           #+#    #+#             */
/*   Updated: 2024/02/13 12:13:24 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

unsigned int	f_randi(uint32_t idx)
{
	idx = (idx << 13) ^ idx;
	return ((idx * (idx * idx * 15731 + 789221) + 1376312589) & 0x7fffffff);
}

unsigned int	f_rand(void)
{
	return (rand() % 100);
}
