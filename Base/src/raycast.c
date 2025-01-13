/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:09:48 by pauberna          #+#    #+#             */
/*   Updated: 2025/01/08 17:07:11 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_build_image(t_data *data)
{
	if (data->move == true)
	{
		key_check1(data);
		key_check2(data);
	}
	if (data->keys[4] == 1 && data->move == true)
		ft_rotation(data, -KEY_ROT);
	else if (data->keys[5] == 1 && data->move == true)
		ft_rotation(data, KEY_ROT);
	ft_build_sky_floor(data);
	render_first_layer(data);
}

void	set_ray_dir_and_dist(t_data *data, t_vars *vars)
{
	vars->camera_x = 2 * vars->x / (double)W_WIDTH - 1;
	vars->ray_dir_x = data->plr.cam.dir.x + \
		data->plr.cam.plane.x * vars->camera_x;
	vars->ray_dir_y = data->plr.cam.dir.y + \
		data->plr.cam.plane.y * vars->camera_x;
	vars->map_x = (int)data->plr.pos.x;
	vars->map_y = (int)data->plr.pos.y;
	vars->delta_dist_x = fabs(1 / vars->ray_dir_x);
	vars->delta_dist_y = fabs(1 / vars->ray_dir_y);
}

void	set_ray_side_dist(t_data *data, t_vars *vars)
{
	if (vars->ray_dir_x < 0)
	{
		vars->step_x = -1;
		vars->side_dist_x = (data->plr.pos.x - vars->map_x) \
			* vars->delta_dist_x;
	}
	else
	{
		vars->step_x = 1;
		vars->side_dist_x = (vars->map_x + 1.0 - data->plr.pos.x) \
			* vars->delta_dist_x;
	}
	if (vars->ray_dir_y < 0)
	{
		vars->step_y = -1;
		vars->side_dist_y = (data->plr.pos.y - vars->map_y) \
			* vars->delta_dist_y;
	}
	else
	{
		vars->step_y = 1;
		vars->side_dist_y = (vars->map_y + 1.0 - data->plr.pos.y) \
			* vars->delta_dist_y;
	}
}

void	set_dist_to_wall(t_data *data, t_vars *vars, int mode)
{
	while (42)
	{
		if (vars->side_dist_x < vars->side_dist_y)
		{
			vars->side_dist_x += vars->delta_dist_x;
			vars->map_x += vars->step_x;
			vars->side = 0;
		}
		else
		{
			vars->side_dist_y += vars->delta_dist_y;
			vars->map_y += vars->step_y;
			vars->side = 1;
		}
		if (mode == 0 && data->map[vars->map_y][vars->map_x] == '1')
			break ;
	}
}

void	set_draw_len(t_data *data, t_vars *vars)
{
	if (vars->side == 0)
		vars->wall_dist = (vars->map_x - data->plr.pos.x \
			+ (1 - vars->step_x) / 2) / vars->ray_dir_x;
	else
		vars->wall_dist = (vars->map_y - data->plr.pos.y \
			+ (1 - vars->step_y) / 2) / vars->ray_dir_y;
	vars->line_height = (int)(W_HEIGHT / vars->wall_dist);
	vars->draw_start = -vars->line_height / 2 + W_HEIGHT / 2;
	if (vars->draw_start < 0)
		vars->draw_start = 0;
	vars->draw_end = vars->line_height / 2 + W_HEIGHT / 2;
	if (vars->draw_end >= W_HEIGHT)
		vars->draw_end = W_HEIGHT - 1;
	if (vars->side == 0)
		vars->wall_x = data->plr.pos.y + vars->wall_dist * vars->ray_dir_y;
	else
		vars->wall_x = data->plr.pos.x + vars->wall_dist * vars->ray_dir_x;
	vars->wall_x -= floor(vars->wall_x);
	vars->tex_x = (int)(vars->wall_x * TEXTURE_SIZE);
	if ((vars->side == 0 && vars->ray_dir_x < 0) \
		|| (vars->side == 1 && vars->ray_dir_y > 0))
		vars->tex_x = TEXTURE_SIZE - vars->tex_x - 1;
	vars->step = (double)TEXTURE_SIZE / vars->line_height;
	vars->pos = (vars->draw_start - W_HEIGHT / 2 + vars->line_height / 2) \
		* vars->step;
}
