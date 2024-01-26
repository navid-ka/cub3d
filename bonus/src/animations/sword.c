/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sword.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- <nkeyani-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 23:16:11 by bifrost           #+#    #+#             */
/*   Updated: 2024/01/26 10:17:25 by nkeyani-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <sys/time.h>
#include <stdint.h>


char *add_file_extension(char *file, int num)
{
    char *new_file;
    char *num_str;

    new_file = malloc(ft_strlen(file) + 1);
    num_str = ft_itoa(num);
    ft_memcpy(new_file, file, ft_strlen(file) + 1);
    ft_strlcat(new_file, num_str, ft_strlen(file) + ft_strlen(num_str) + 1);
    ft_strlcat(new_file, ".xpm", ft_strlen(file) + ft_strlen(num_str) + 5);
    free(num_str);
    return new_file;
}

void load_sword_img(t_mlx *g)
{
    int i;
    char *file;

    file = "textures/sword/sword";
    i = 0;
    g->sword = malloc(sizeof(t_img) * 32);
    while (i < 30)
    {
        int width = 1008;
        int height = 874;
        g->sword[i].img = mlx_xpm_file_to_image(g->mlx_p,
            add_file_extension(file, i), &width, &height);
        g->sword[i].addr = mlx_get_data_addr(g->sword[i].img, &g->sword[i].bpp, 
            &g->sword[i].line_len, &g->sword[i].endian);
        g->sword[i].width = width;
        g->sword[i].height = height;
        i++;
    }
}

int    draw_idle(t_game *game)
{
    int y = game->mlx_s->screen_height - game->mlx_s->sword[0].height + 300;
    int x = (game->mlx_s->screen_width - game->mlx_s->sword[0].width) / 2;

    put_img_to_img(game->mlx_s->buffer, &game->mlx_s->sword[0], x, y);
    return (IDLE);
}

int draw_sword_animation(t_game *game)
{
    static int i = 0;
    int y = game->mlx_s->screen_height - game->mlx_s->sword[0].height + 300;
    int x = (game->mlx_s->screen_width - game->mlx_s->sword[0].width) / 2;

    if (i < 30)
    {
        put_img_to_img(game->mlx_s->buffer, &game->mlx_s->sword[i], x, y);
        i++;
    }
    if (i == 30)
    {
        game->sword_state = IDLE;
        i = 0;
    }
    else
        game->sword_state = ATACK;
    return (game->sword_state);
}

int	sword_manager(t_game *g, enum e_sword state)
{
	static const t_state_manager	sword_state_lookup[3] = {
	[IDLE] = {draw_idle},
	[ATACK] = {draw_sword_animation},
	};

	g->sword_state = state;
	return (sword_state_lookup[state].f(g));
}
