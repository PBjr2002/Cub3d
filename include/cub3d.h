/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:01:29 by adimas-d          #+#    #+#             */
/*   Updated: 2025/01/08 17:10:26 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "mlx/mlx.h"
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/resource.h>
# include <signal.h>
# include <errno.h>
# include <stdbool.h>
# include <math.h>
# include <X11/keysym.h>
# include <X11/X.h>

# define ESC_KEY 65307
# define U_ARR_KEY 65362
# define D_ARR_KEY 65364
# define L_ARR_KEY 65361
# define R_ARR_KEY 65363
# define W_KEY 119
# define S_KEY 115
# define A_KEY 97
# define D_KEY 100
//# define W_WIDTH 3840
//# define W_HEIGHT 1860
# define W_WIDTH 1920
# define W_HEIGHT 1080
# define KEY_ROT 0.04
# define MOVE_SPEED 0.1
# define TEXTURE_SIZE 256
# define FRAME_R 60

typedef struct s_timeval
{
	time_t			tv_sec;
	suseconds_t		tv_usec;
}				t_timeval;

typedef struct s_vector
{
	float	x;
	float	y;
}				t_vector;

typedef struct s_ray
{
	double		camera_x;
	t_vector	dir;
}				t_ray;

typedef struct s_cam
{
	t_vector	dir;
	t_vector	plane;
}				t_cam;

typedef struct s_plr
{
	t_vector	pos;
	t_cam		cam;
	t_ray		ray[W_WIDTH];
}				t_plr;

typedef struct s_img
{
	void		*mlx_img;
	char		*addr;
	int			bits_per_pixel;
	int			width;
	int			height;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_window;
	t_img		img;
	int			column_count;
	int			line_count;
	int			width;
	int			height;
	float		x_step;
	float		y_step;
	float		x;
	float		y;
	float		hitbox;
	int			color;
	char		**map;
	char		**og_map;
	char		*file_name;
	t_img		*n_wall;
	t_img		*s_wall;
	t_img		*e_wall;
	t_img		*w_wall;
	char		*north_text;
	char		*south_text;
	char		*east_text;
	char		*west_text;
	int			fd;
	t_plr		plr;
	int			floor;
	int			ceiling;
	int			keys[6];
	t_timeval	*timeval;
	long		frame;
	bool		move;
}				t_data;

typedef struct s_check
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	double		wall_dist;
	float		limit;
	t_vector	pos;
	int			x;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			side;
}				t_check;

typedef struct s_vars
{
	int		x;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_x;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	double	wall_dist;
	double	wall_x;
	double	pos;
	double	step;
}				t_vars;

//main.c

//init_vars.c
void			init_data(t_data *model);
void			init_walls(t_data *model);
void			vars_init(t_vars *vars);

//window.c
int				render(void *src);
int				ft_close_window(t_data *model);
void			ft_creat_window(t_data *model);

//parsing.c
int				map_lines_counter(char *map);
int				parsing(t_data *data, char *file);
int				check_file(char *file, int mode);
int				check_file_name(char *map_name, char *str);
void			set_data(t_data *data, char *file);

//map_constructor.c
void			construct_map(t_data *data, int n);
void			get_map_info(t_data *data);
int				get_dptr_info(t_data *data, int n, int *i);
int				texture_storage(t_data *data, int n, int i);
int				get_map_height(char **map, int n);

//map_normalizer.c
void			map_normalizer(t_data *data, int map_height);
void			free_dptr(char **dptr);
char			*resize_line(char *line, int map_width);
int				find_width(char **map);
int				find_height(char **map);

//get_textures.c
int				get_texture(t_data *data, char *texture);
char			*get_texture_path(char *str);
int				get_color(char *str);
int				mini_atoi(char *str, int *index);
t_img			*new_file_img(char *path, void *mlx);

//get_player_info.c
void			get_player_info(t_data *data);
void			player_init(t_plr *player);
void			set_player_direction(t_data *data);
void			set_player_dir(t_data *data, float target_x, float target_y);

//check_map.c
int				check_walls(t_data *data);
int				check_middle(char **map);
int				check_for_player(t_data *data);
int				check_top_bottom(char **map, int line_c);
int				check_left_right(char **map, int column_c);

//check_content.c
int				check_map_content(t_data *data);
int				check_xpms(t_data *data);

//movement.c
int				is_there_a_wall(t_data *data, int mode);
int				check_move(t_data *data, t_vector new_pos, int mode);

//check_move_utils.c
void			dir_and_dist_setter(t_data *data, t_check *plr, int mode);
void			dir_setter(t_data *data, t_check *plr, int mode);
void			set_ray_dir(t_data *data, t_check *plr, double value);
void			get_side_dist(t_check *plr);
void			get_dist_to_wall(t_data *data, t_check *plr);

//keys.c
int				ft_key_push(int keycode, t_data *model);
int				ft_key_release(int keycode, t_data *model);
void			key_check1(t_data *data);
void			key_check2(t_data *data);
void			ft_rotation(t_data *model, float value);

//draw_texture.c
void			draw_texture(t_data *data, t_img *img, t_vars *vars);
void			my_mlx_pixel_put(t_data *model, int x, int y, int color);
unsigned int	get_pixel_img(t_img *img, int x, int y);
void			ft_creat_image(t_data *model, int x, int y);

//raycast.c
void			ft_build_image(t_data *data);
void			set_ray_dir_and_dist(t_data *data, t_vars *vars);
void			set_ray_side_dist(t_data *data, t_vars *vars);
void			set_dist_to_wall(t_data *data, t_vars *vars, int mode);
void			set_draw_len(t_data *data, t_vars *vars);

//raycast_utils.c
void			ft_build_sky_floor(t_data *data);
void			render_first_layer(t_data *data);

//free_stuff.c
void			free_data(t_data *data);
void			free_text(t_data *data);
void			free_imgs(t_data *data);
void			free_door(t_data *data);
void			verify_elements(t_data *data, int flag);

#endif
