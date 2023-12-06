/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:19:26 by bifrost           #+#    #+#             */
/*   Updated: 2023/12/06 16:58:55 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <X11/keysym.h>

//https://www.cl.cam.ac.uk/~mgk25/ucs/keysymdef.h for keycodes

int window_destroy(t_mlx *window)
{
    mlx_destroy_window(window->mlx, window->win);
    exit(0);
}
int	handle_input(int keysym, t_mlx *window)
{
    if (keysym == XK_Escape)
        window_destroy(window);
    return (0);
}

void    window_init(t_mlx *window)
{
    window->mlx = mlx_init();
    window->win = mlx_new_window(window->mlx, 640, 480, "Cub3D");
    mlx_key_hook(window->win, handle_input, window);
	mlx_hook(window->win, 17, 0, &window_destroy, window);
    mlx_hook(window->win, 2, 0, &handle_input, window);
    mlx_loop(window->mlx);
}