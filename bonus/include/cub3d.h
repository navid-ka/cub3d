/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:26:27 by nkeyani-          #+#    #+#             */
/*   Updated: 2024/03/17 16:49:49 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <libft.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdint.h>
# include <errno.h>
# include <time.h>

# define NORTH 100
# define SOUTH 200
# define EAST 300
# define WEST 400

# define PI 3.14159265358979323846
# define S_WIDTH 1280
# define S_HEIGHT 720
# define MOVE_SPEED 0.025
# define ROTATE_SPEED 0.050
# define FOV 160
# define RENDER_DIST 10 //* 32 + 16
# define PI 3.14159265358979323846
# define SECONDS 1000
# define HP_PLAYER 20
# define HP_ENEMY_BASE 10
# define HP_BOSS_BASE 10
# define TIMETOGETHIT 10000
# define ESC	53
# define RETURN 36
# define TAB 48
# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define ARROW_UP 126
# define ARROW_DOWN 125
# define A 0
# define W 13
# define S 1
# define D 2
# define E 14
# define KEY_ESC 53
# define DOOR_MAX_DISTANCE 32
# define ARGC "Error\nToo many arguments\n"

# define MOVE_DISTANCE 1
# define MAX_DISTANCE 5

typedef unsigned char	t_uic8;

typedef struct s_player
{
	double	fov;	// field of view is 90 degrees
	double	pos_x; //position
	double	pos_y;
	double	dir_x; //direction
	double	dir_y;
	double	angle;	// in radians
	double	speed;
	double	dx;
	double	dy;
	int		dg_angle;
	double	distance;
	bool	door_collision;
	int		hp;
	double	dmg;
	int		exp;
	int		lvl;
}	t_player;

enum	e_type
{
	NORMAL,
	BOSS
};

typedef struct s_enemy
{
	double		hp;
	double		lvl;
	double		armor;
	double		dmg;
	enum e_type	type;
}	t_enemy;

typedef struct s_line
{
	double	y_start;
	double	y_end;
	double	x_start;
	double	x_end;
	int		draw_start;
	int		draw_end;
	int		line_height;
	int		color;
	int		color_fader;
	int		text_x;
	double	step;
	double	text_pos;
	double	brightness;
	int		text_y;
	int		offset;
	int		w;
}	t_line;

typedef struct s_camera
{
	double	plane_multiplier;
	double	plane_x;
	double	plane_y;
	double	camera_x;
	double	camera_y;
	int		map_x;
	int		map_y;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		hit_direction;
	double	wall_x;
	char	type;
	int		door_state;
}	t_camera;

typedef struct s_position
{
	int	x;
	int	y;
}	t_position;

typedef struct s_map
{
	int			width;
	int			height;
	char		**map;
	char		**tmp_map;
	int			orientation;
}	t_map;

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

typedef struct s_cub
{
	char	**map;
	char	*tmp;
	char	*new_tmp;
	char	*path;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f_color;
	t_color	floor;
	char	*c_color;
	t_color	ceiling;
	int		count;
	int		err;
}	t_cub;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_mlx
{
	void	*mlx_p;
	void	*win;
	t_img	*buffer;
	t_img	sword[30];
	t_img	enemy[2];
	t_img	enemy_hit[2];
	t_img	img[6];
	t_img	wall[5];
	t_img	door[16];
	t_img	fonts[94];
	double	mouse_x;
	double	mouse_y;
	int		screen_height;
	int		screen_width;
}	t_mlx;

typedef struct s_game
{
	t_mlx		*mlx_s;
	t_map		*map_s;
	t_cub		*cub_s;
	t_player	*player_s;
	t_camera	*camera_s;
	t_enemy		*enemy;
	int			state;
	int			sword_state;
	int			door_state;
	int			door_offset;
	int			steps;
	uint32_t	random;
	uint64_t	created_at;
	uint64_t	updated_at;
	uint64_t	combat_started_at;
	uint64_t	frame_count;
	uint64_t	text_draw_frame;
	int			door_frame_index;
	int			fps;
	size_t		total_dmg;
}	t_game;

enum e_state
{
	TITLE,
	GAME,
	COMBAT,
	PAUSE,
	END
};

enum e_sword
{
	IDLE,
	ATACK
};

enum e_door
{
	CLOSE,
	OPEN,
};

typedef struct state_manager
{
	int	(*f)(t_game *);
}	t_state_manager;

int			screen_manager(t_game *g, enum e_state state);
int			game_start(t_game *game);
uint64_t	timestamp_in_ms(t_game *game);
uint64_t	gettimeofday_ms(void);
void		load_enemy_img(t_mlx *g);
void		load_enemy_hit(t_mlx *g);
void		load_fonts(t_mlx *g);
void		load_door_img(t_mlx *g);
void		draw_str_to_font(t_mlx *g, char *str, int x, int y);
void		game_save(t_game *game);
void		load_save_file(t_game *game);
t_img		*create_buffer(t_mlx *g, int w, int h);
int			door_manager(t_game *g, enum e_door state);
int			door_handler(t_game *game);
char		*add_file_extension(char *file, int num);

// Parser
void		fd_parser(t_game *game, char **argv);

// Init structs
void		game_init(t_game *game);
void		cub_init(t_cub *init, char **argv);
void		map_init(t_map *map);
void		player_init(t_player *player);
void		window_init(t_mlx *window);
void		sl_image_init(t_mlx *g);
void		walls_image_init(t_game *g);

// FD utils
int			open_path(t_cub *cub, t_map *map);
char		*fd_setter(t_cub *cub, char *line);
int			cub_atoi(const char *str, t_cub *cub);
void		fd_print(t_cub *cub);

// orientation
int			fd_orientation_checker(t_cub *cub, char *line, int *flag);

// colors
int			fd_color_checker(t_cub *cub, char *line, int *flag);

// FD checker
void		fd_check_extension(t_cub *cub);
void		fd_check_integrity(t_cub *cub, t_map *map);

// Map parser
void		map_lengh(t_map *map);
int			orientation_char(char cub);
int			around_zero(t_cub *cub, int index, char *line, int i);
int			around_pl(t_cub *cub, int i, int index);
int			check_possiblty(char c);
void		map_parser(t_game *game, t_cub *cub, t_map *map);

// Mlx
void		mlx_window(t_game *game);
void		camera_init(t_camera *camera, t_player *player);
double		plane_mult(double fov);

//Inputs
double		move_rot(t_camera *cam, t_player *p, char **map, int dir);
int			on_mouse_click(int button, int x, int y, t_game *game);
void		look_with_mouse(t_game *game);
int			on_key_press(int keycode, t_game *game);
int			on_key_release(int keycode, t_game *game);
void		move_forward(t_player *player, t_game *game);
void		move_backward(t_player *player, t_game *game);
void		move_left(t_player *player, t_game *game);
void		move_right(t_player *player, t_game *game);
void		player_move(int keycode, t_player *player, t_game *game);
int			check_door_collision(t_game *game);
void		toggle_door_state(t_player *player, int keycode, t_game *game);
int			check_collision_x(t_game *game, double dx, char *wall, \
				double margin);
int			check_collision_y(t_game *game, double dy, char *wall, \
				double margin);
int			collision_checker(t_game *game, double dx, double dy);

//Raycast or angles
void		init_line(t_line *line, t_camera *c, int i);
void		init_dda(t_line *line, t_player *p, t_camera *c, char **map);
void		init_step(t_player *p, t_camera *c);
void		init_ray(t_player *p, t_camera *c, int i);
void		raycast(t_game *game);
double		deg_to_rad(double dg_angle);
int			rad_to_dg(double angle);
void		draw_line(t_game *game, t_line *line, t_img *img, t_img *src_img);
void		draw(t_game *g, t_camera *cub, t_img *image, t_line *line);
double		apply_fog(t_game *game);
int			get_pixel_color(t_img *img, int x, int y, double brightness);
int			colors(t_color *c);
int			char_to_int(t_uic8 t, t_uic8 r, t_uic8 g, t_uic8 b);

// Anim
int			update(t_game *game);

// Sword
void		load_sword_img(t_mlx *g);
int			draw_idle(t_game *game);
int			draw_sword_animation(t_game *game);
int			sword_manager(t_game *g, enum e_sword state);

// minimap
void		draw_minimap(t_game *g);

// Combat
void		paint_enemy_sprite_white(t_game *g);
int			combat(t_game *g);
void		handle_battle_click(t_game *g);
void		combat_manager(t_game *g);
int			enemy_type_stats(t_game *g, int type);
int			enemy_type_sprites(t_game *g, int type);
void		paint_mid_wall(t_game *g);
void		combat_stats_ui(t_game *g);

// Combat DMG
void		hit_enemy(t_game *g);
void		recieve_damage_afk(t_game *game);
void		level_player_up(t_game *g);
void		level_enemy_up(t_game *g);
int			check_hp_players(t_game *g);

// Img utils
t_img		create_new_img(t_mlx *g, int width, int height);
void		put_pixel_img(t_img *img, int x, int y, int color);
void		put_img_to_img(t_img *dst, t_img *src, int x, int y);
uint32_t	get_pixel_img(t_img *img, int x, int y);
t_img		resize_image(t_mlx *g, t_img img, int nw, int nh);
void		img_pix_put(t_img *img, int x, int y, int color);
t_img		load_img(t_mlx *g, char *path, int w, int h);

// Math
uint32_t	f_randi(uint32_t idx);
uint32_t	f_rand(void);

//Garbage collectors
int			window_destroy(t_game *game);
void		free_tab(char **args);
void		free_textures(t_cub *cub);
void		free_null(char **ptr);
void		fd_error(t_cub *cub, t_map *map, int err);
void		garbage_collector(t_game *game);
void		free_images(t_mlx *g);
void		free_img(t_mlx *g, t_img *img);
void		fd_error_2(t_cub *cub, t_map *map);
void		fd_error_1(t_cub *cub, t_map *map);
void		fd_error_3(t_game *game, t_cub *cub, t_map *map);

#endif