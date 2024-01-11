/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:46:57 by bifrost           #+#    #+#             */
/*   Updated: 2024/01/11 20:47:18 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <sys/time.h>
#include <stdint.h>

static uint64_t	gettimeofday_ms(void) 
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

uint64_t	timestamp_in_ms(t_game *game) 
{
	if (game->created_at == 0)
		game->created_at = gettimeofday_ms();
    //printf("timestamp: %lu\n", gettimeofday_ms());
	return (gettimeofday_ms() - game->created_at);
}