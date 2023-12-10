/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_linux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:19:26 by bifrost           #+#    #+#             */
/*   Updated: 2023/12/10 18:07:40 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <X11/keysym.h>

//https://www.cl.cam.ac.uk/~mgk25/ucs/keysymdef.h for keycodes

int window_destroy(t_game *game)
{

    mlx_destroy_window(game->mlx_s->mlx_p, game->mlx_s->win);
    garbage_collector(game);
    exit(0);
}

int	handle_input(int keysym, t_game *game)
{
    printf("keycode: %d\n", keysym);
    if (keysym == XK_Escape)
        return (window_destroy(game));
    return (0);
}

void    mlx_window(t_game *game)
{
    t_mlx   *window;

    window = game->mlx_s;
    window_init(window);
    window->mlx_p = mlx_init();
    window->win = mlx_new_window(window->mlx_p, 640, 480, "Cub3D");
    mlx_key_hook(window->win, handle_input, game);
	mlx_hook(window->win, 17, 0, window_destroy, game);
    if (mlx_hook(window->win, 2, 0, handle_input, game) == 1)
        return ;
    mlx_loop(window->mlx_p);
}
