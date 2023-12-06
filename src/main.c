/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:24:47 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/12/06 15:29:12 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int main(int argc, char **argv)
{
	t_cub		cub;
	t_player	p1;
	t_mlx		window;

	(void)p1;
	if (argc > 2 || argc < 2)
		return (printf(ARGC));
	
	fd_parser(&cub, argv + 1);
    ft_cast_rays(&p1, cub.map);
	window_init(&window);
	//garbage_collector(&cub);
	return (0);
}
