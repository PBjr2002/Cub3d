/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_move_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:57:25 by pauberna          #+#    #+#             */
/*   Updated: 2025/01/06 18:06:37 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	dir_and_dist_setter(t_data *data, t_check *plr, int mode)
{
	plr->camera_x = 2 * plr->x / (double)W_WIDTH - 1;
	plr->ray_dir_x = 0;
	plr->ray_dir_y = 0;
	plr->map_x = (int)plr->pos.x;
	plr->map_y = (int)plr->pos.y;
	dir_setter(data, plr, mode);
	plr->delta_dist_x = fabs(1 / plr->ray_dir_x);
	plr->delta_dist_y = fabs(1 / plr->ray_dir_y);
}

void	dir_setter(t_data *data, t_check *plr, int mode)
{
	if (mode == 0 || mode == 4)
	{
		plr->ray_dir_x = data->plr.cam.dir.x \
			+ data->plr.cam.plane.x * plr->camera_x;
		plr->ray_dir_y = data->plr.cam.dir.y \
				+ data->plr.cam.plane.y * plr->camera_x;
	}
	else if (mode == 1)
		set_ray_dir(data, plr, M_PI);
	else if (mode == 2)
		set_ray_dir(data, plr, -M_PI / 2);
	else if (mode == 3)
		set_ray_dir(data, plr, M_PI / 2);
}

void	set_ray_dir(t_data *data, t_check *plr, double value)
{
	plr->ray_dir_x = (data->plr.cam.dir.x * cos(value) \
		- data->plr.cam.dir.y * sin(value)) \
			+ data->plr.cam.plane.x * plr->camera_x;
	plr->ray_dir_y = (data->plr.cam.dir.x * sin(value) \
		+ data->plr.cam.dir.y * cos(value)) \
			+ data->plr.cam.plane.y * plr->camera_x;
}

void	get_side_dist(t_check *plr)
{
	if (plr->ray_dir_x < 0)
	{
		plr->step_x = -1;
		plr->side_dist_x = (plr->pos.x - plr->map_x) * plr->delta_dist_x;
	}
	else
	{
		plr->step_x = 1;
		plr->side_dist_x = (plr->map_x + 1.0 - plr->pos.x) * plr->delta_dist_x;
	}
	if (plr->ray_dir_y < 0)
	{
		plr->step_y = -1;
		plr->side_dist_y = (plr->pos.y - plr->map_y) * plr->delta_dist_y;
	}
	else
	{
		plr->step_y = 1;
		plr->side_dist_y = (plr->map_y + 1.0 - plr->pos.y) * plr->delta_dist_y;
	}
}

void	get_dist_to_wall(t_data *data, t_check *plr)
{
	while (42)
	{
		if (data->map[plr->map_y][plr->map_x] == '1')
			break ;
		if (plr->side_dist_x < plr->side_dist_y)
		{
			plr->side_dist_x += plr->delta_dist_x;
			plr->map_x += plr->step_x;
			plr->side = 0;
		}
		else
		{
			plr->side_dist_y += plr->delta_dist_y;
			plr->map_y += plr->step_y;
			plr->side = 1;
		}
	}
}
