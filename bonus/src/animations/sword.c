/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sword.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 23:16:11 by bifrost           #+#    #+#             */
/*   Updated: 2023/12/31 11:05:58 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <sys/time.h>
#include <stdint.h>

uint64_t created_at = 0;

static uint64_t	gettimeofday_ms(void) {
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

uint64_t	timestamp_in_ms(void) {
	if (created_at == 0)
		created_at = gettimeofday_ms();
	return (gettimeofday_ms() - created_at);
}


char *add_file_extension(char *file, int num)
{
    char *new_file;
    char *num_str;

    new_file = malloc(ft_strlen(file) + 10);
    num_str = ft_itoa(num);
    ft_memcpy(new_file, file, ft_strlen(file) + 1); // Copia también el carácter nulo
    ft_strlcat(new_file, num_str, ft_strlen(file) + ft_strlen(num_str) + 1);
    ft_strlcat(new_file, ".xpm", ft_strlen(file) + ft_strlen(num_str) + 5);
    free(num_str);
    return new_file;
}

void    load_sword_img(t_mlx *g)
{
    int i;
    int sword_width;
    int sword_height;
    char *file;

    sword_width = 1008;
    sword_height = 874;
    file = "textures/sword/sword";
    i = 0;
    g->sword = malloc(sizeof(t_img) * 31 + 1);
    while (i < 30)
    {
        //printf("file: %s\n", add_file_extension(file, i));
        g->sword[i].img = mlx_xpm_file_to_image(g->mlx_p,
        add_file_extension(file, i), &sword_width, &sword_height);
        i++;
    }
    
}

int    draw_idle(t_game *game)
{
    //static int i = 0;
    int y = (int)game->player_s->pos_y;
    int x = (int)game->player_s->pos_x;
    //if (++i < 4)
   // {
   //     usleep(1000000 / game->fps * 5);
    mlx_put_image_to_window(game->mlx_s->mlx_p, game->mlx_s->win, game->mlx_s->sword[0].img, x, y + 90);
   // }
   // else
   //     i = 0;
    return (IDLE);
}

int draw_sword_animation(t_game *game)
{
    static int i = 0;
    int y = (int)game->player_s->pos_y;
    int x = (int)game->player_s->pos_x;

    if (i < 30)
    {
        mlx_put_image_to_window(game->mlx_s->mlx_p, game->mlx_s->win, game->mlx_s->sword[i].img, x, y + 90);
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

int update(t_game *game) 
{
    static uint64_t updated_at = 0;

    if (timestamp_in_ms() - updated_at < (uint64_t)(1000 / game->fps))
        return 0;
    updated_at = timestamp_in_ms();
    printf("timestamp: %ld\t update: %ld, FPS: %d\n", timestamp_in_ms(), updated_at, game->fps);  
    game->sword_state = sword_manager(game, game->sword_state);
    return 0;
}
