/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- <nkeyani-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 04:01:07 by bifrost           #+#    #+#             */
/*   Updated: 2024/02/02 15:59:39 by nkeyani-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

unsigned int f_randi(uint32_t idx)
{
	idx = (idx << 13) ^ idx;
	return ((idx * (idx * idx * 15731 + 789221) + 1376312589) & 0x7fffffff);
}

unsigned int f_rand(void) 
{
    return rand() % 100;    
}

void paint_mid_wall(t_game *g)
{
    int i;
    int j;
    t_img img;

    img.img = mlx_new_image(g->mlx_s->mlx_p, S_WIDTH, S_HEIGHT);
    img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
    img.height = S_HEIGHT;
    img.width = S_WIDTH;
    i = 0;
    while (i < S_WIDTH)
    {
        j = S_HEIGHT / 2 - g->mlx_s->wall[4].height / 2;
        while (j < S_HEIGHT / 2 + g->mlx_s->wall[4].height / 2)
        {
            if (j >= 0 && j < S_HEIGHT)
            {
                int sprite_y = (j - (S_HEIGHT / 2 - g->mlx_s->wall[0].height / 2)) * g->mlx_s->wall[0].height / g->mlx_s->wall[0].height; 
                img_pix_put(&img, i, j, get_pixel_img(&g->mlx_s->wall[3], i % g->mlx_s->wall[0].width, sprite_y));
            }
            j++;
        }
        i++;
    }
    put_img_to_img(g->mlx_s->buffer, &img, 0, 0);
    mlx_destroy_image(g->mlx_s->mlx_p, img.img);
}

void paint_enemy_sprite_white(t_game *g)
{
    put_img_to_img(g->mlx_s->buffer, &g->mlx_s->enemy_hit[g->random], 
        (g->mlx_s->screen_width - g->mlx_s->enemy_hit[g->random].width) / 2, 
        (g->mlx_s->screen_height - g->mlx_s->enemy_hit[g->random].height) / 2);

    // esto produce un efecto de flash blanco en toda la pantalla durante un frame
    //buscar mejor forma de pushear el effecto a la pantalla
    mlx_put_image_to_window(g->mlx_s->mlx_p, g->mlx_s->win, g->mlx_s->buffer->img, 0, 0);
}

void level_enemy_up(t_game *g) 
{
    g->enemy->lvl++;
    g->enemy->dmg += 0.50;
    g->enemy->armor += 0.15;
    printf("Enemy lvl: %f\n", g->enemy->lvl);
}

void level_player_up(t_game *g)
{
    g->player_s->exp += ((g->enemy->lvl / 2) * 10);
    //ft_printf("exp: %d\n", g->player_s->exp);
    if (g->player_s->exp > 100)
    {
        g->player_s->lvl++;
        g->player_s->exp = 0;
        g->player_s->dmg += 3 * 0.75;
    }
}

void hit_enemy(t_game *g) 
{
    g->enemy->hp -= (int)(g->player_s->dmg - g->enemy->armor);
    paint_enemy_sprite_white(g);
    printf("Enemy hp: %f\n", g->enemy->hp);
}

void handle_battle_click(t_game *g) 
{
    if(g->sword_state == 1)
    {
        hit_enemy(g);
        g->total_dmg += (int)(g->player_s->dmg - g->enemy->armor);
    }
}

int check_hp_players(t_game *g) 
{
    if(g->enemy->hp <= 0) {
        level_enemy_up(g);
        level_player_up(g);
        game_save(g);
        g->state = screen_manager(g, GAME);
        return (GAME);
    }
    if(g->player_s->hp <= 0)
    {
        printf("You died\n");
        g->combat_started_at = 0;
        g->state = screen_manager(g, END);
        return (END);
    }
    return (g->state);
}

void recieve_damage_afk(t_game *game) 
{
    game->player_s->hp -= 1;
    printf("Recibimos daño por no matarlo antes de tiempo\n");
    printf("Vida actual %d\n", game->player_s->hp);
}

void check_combat_status(t_game *g)
{
    int status_end;
    status_end = g->state;
    status_end = check_hp_players(g);
    if(status_end == GAME) {
        g->state = screen_manager(g, GAME);
    }
    else if(status_end == END) {
        g->player_s->hp = HP_PLAYER;
        g->state = screen_manager(g, END);
    }
    //leak
    
    draw_str_to_font(g->mlx_s, "Getting hit in", 
    (g->mlx_s->screen_width - (g->mlx_s->enemy->width - (g->mlx_s->enemy->width / 2))) / 2 + 150, 250);
    draw_str_to_font(g->mlx_s, ft_itoa((TIMETOGETHIT - (g->updated_at - g->combat_started_at) - 1) / 1000), 
            (g->mlx_s->screen_width - (g->mlx_s->enemy->width - (g->mlx_s->enemy->width / 2))) / 2 + 150, 300);
    draw_str_to_font(g->mlx_s, "DPS METER", 
                (g->mlx_s->screen_width - (g->mlx_s->enemy->width - (g->mlx_s->enemy->width / 2))) / 2 - 150, 250);
    draw_str_to_font(g->mlx_s, ft_itoa(g->total_dmg), 
                (g->mlx_s->screen_width - (g->mlx_s->enemy->width - (g->mlx_s->enemy->width / 2))) / 2 - 150, 300);
    if(g->updated_at - g->combat_started_at > TIMETOGETHIT && status_end != END) {
        recieve_damage_afk(g);
        g->combat_started_at = g->updated_at;
    }
}

int combat(t_game *g)
{
    g->random = f_rand() % 2;
    g->combat_started_at = timestamp_in_ms(g);
    enemy_type_stats(g, g->random);
    g->steps = 0;
    g->total_dmg = 0;
    printf("Enemy hp: %f Enemy lvl: %f\n", g->enemy->hp, g->enemy->lvl);
    printf("Entered combat\n");
    return (COMBAT);
}

void combat_manager(t_game *g) 
{
    char *str;

    str = NULL;
    str = ft_itoa(g->enemy->hp);
    draw_str_to_font(g->mlx_s, str, 
        (g->mlx_s->screen_width - (g->mlx_s->enemy->width - (g->mlx_s->enemy->width))) / 2, 200);
    free_null(&str);
    enemy_type_sprites(g, g->random);
    check_combat_status(g);
}
