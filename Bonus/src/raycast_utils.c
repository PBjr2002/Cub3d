/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 10:26:09 by pauberna          #+#    #+#             */
/*   Updated: 2025/01/06 18:04:58 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	check_if_door(t_data *data, t_vars *vars, int mode)
{
	if ((mode == 1 || mode == 2) && (data->map[vars->map_y][vars->map_x] == '1'
		|| data->map[vars->map_y][vars->map_x] == 'D'))
	{
		if (data->map[vars->map_y][vars->map_x] == 'D')
		{
			vars->door_num = find_door_num(data, vars->map_x, vars->map_y);
			if (mode == 1 && data->door[vars->door_num].open != 0)
				return (2);
			else if (mode == 2 && data->door[vars->door_num].open != 0)
				return (1);
		}
		return (1);
	}
	return (0);
}

void	ft_build_sky_floor(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->height / 2)
	{
		x = 0;
		while (x < data->width)
		{
			my_mlx_pixel_put(data, x, y, data->ceiling);
			x++;
		}
		y++;
	}
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			my_mlx_pixel_put(data, x, y, data->floor);
			x++;
		}
		y++;
	}
}

void	render_first_layer(t_data *data)
{
	t_vars	vars;

	vars_init(&vars);
	while (++(vars.x) < data->width)
	{
		set_ray_dir_and_dist(data, &vars);
		set_ray_side_dist(data, &vars);
		set_dist_to_wall(data, &vars, 0);
		set_draw_len(data, &vars);
		while (vars.draw_start <= vars.draw_end)
		{
			vars.pos += vars.step;
			if (vars.side == 0 && vars.ray_dir_x < 0 \
				&& data->map[vars.map_y][vars.map_x] != 'D')
				draw_texture(data, data->w_wall, &vars);
			else if (vars.side == 0 && data->map[vars.map_y][vars.map_x] != 'D')
				draw_texture(data, data->e_wall, &vars);
			else if (vars.side == 1 && vars.ray_dir_y < 0 \
				&& data->map[vars.map_y][vars.map_x] != 'D')
				draw_texture(data, data->n_wall, &vars);
			else if (vars.side == 1 && data->map[vars.map_y][vars.map_x] != 'D')
				draw_texture(data, data->s_wall, &vars);
			vars.draw_start++;
		}
	}
}

void	render_second_layer(t_data *data)
{
	t_vars	vars;

	vars_init(&vars);
	while (++(vars.x) < data->width)
	{
		set_ray_dir_and_dist(data, &vars);
		set_ray_side_dist(data, &vars);
		set_dist_to_wall(data, &vars, 1);
		set_draw_len(data, &vars);
		while (vars.draw_start <= vars.draw_end)
		{
			vars.pos += vars.step;
			if (data->map[vars.map_y][vars.map_x] == 'D' \
				&& data->door[vars.door_num].open == 0)
				draw_texture(data, data->door_tex[0], &vars);
			vars.draw_start++;
		}
	}
}

void	render_third_layer(t_data *data)
{
	t_vars	vars;

	vars_init(&vars);
	while (++(vars.x) < data->width)
	{
		set_ray_dir_and_dist(data, &vars);
		set_ray_side_dist(data, &vars);
		set_dist_to_wall(data, &vars, 2);
		set_draw_len(data, &vars);
		while (vars.draw_start <= vars.draw_end)
		{
			vars.pos += vars.step;
			if (data->map[vars.map_y][vars.map_x] == 'D' \
				&& data->door[vars.door_num].open == 1)
				draw_texture(data, data->door_tex[1], &vars);
			else if (data->map[vars.map_y][vars.map_x] == 'D' \
				&& data->door[vars.door_num].open == 2)
				draw_texture(data, data->door_tex[2], &vars);
			else if (data->map[vars.map_y][vars.map_x] == 'D' \
				&& data->door[vars.door_num].open == 3)
				draw_texture(data, data->door_tex[3], &vars);
			vars.draw_start++;
		}
	}
}
