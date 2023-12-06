/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:19:26 by bifrost           #+#    #+#             */
/*   Updated: 2023/12/06 16:35:27 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int window_destroy(t_mlx *window)
{
    mlx_destroy_window(window->mlx, window->win);
    exit(0);
}
int window_input(int keycode, t_mlx *window)
{
    printf("Keycode: %d\n", keycode);
    if (keycode == KEY_ESC)
        window_destroy(window);
    return (0);
}

void    window_init(t_mlx *window)
{
    window->mlx = mlx_init();
    window->win = mlx_new_window(window->mlx, 640, 480, "Cub3D");
	mlx_hook(window->win, 17, 0, &window_destroy, window);
    mlx_hook(window->win, 2, 0, &window_input, window);
    mlx_loop(window->mlx);
}