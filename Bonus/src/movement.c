/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:21:31 by pauberna          #+#    #+#             */
/*   Updated: 2025/01/07 11:30:49 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	is_there_a_wall(t_data *data, int mode)
{
	t_vector	new_pos;

	if (mode == 0)
	{
		new_pos.x = data->plr.pos.x + data->plr.cam.dir.x * MOVE_SPEED;
		new_pos.y = data->plr.pos.y + data->plr.cam.dir.y * MOVE_SPEED;
	}
	else if (mode == 1)
	{
		new_pos.x = data->plr.pos.x - data->plr.cam.dir.x * MOVE_SPEED;
		new_pos.y = data->plr.pos.y - data->plr.cam.dir.y * MOVE_SPEED;
	}
	else if (mode == 2)
	{
		new_pos.x = data->plr.pos.x + data->plr.cam.dir.y * MOVE_SPEED;
		new_pos.y = data->plr.pos.y - data->plr.cam.dir.x * MOVE_SPEED;
	}
	else
	{
		new_pos.x = data->plr.pos.x - data->plr.cam.dir.y * MOVE_SPEED;
		new_pos.y = data->plr.pos.y + data->plr.cam.dir.x * MOVE_SPEED;
	}
	if (check_move(data, new_pos, mode) == 1)
		return (1);
	return (0);
}

int	check_move(t_data *data, t_vector new_pos, int mode)
{
	t_check	plr;

	plr.pos.x = new_pos.x;
	plr.pos.y = new_pos.y;
	plr.limit = data->width - (data->width / 10);
	plr.x = data->width - plr.limit;
	plr.door_num = 0;
	while (plr.x < plr.limit)
	{
		dir_and_dist_setter(data, &plr, mode);
		get_side_dist(&plr);
		get_dist_to_wall(data, &plr);
		if (plr.side == 0)
			plr.wall_dist = (plr.map_x - new_pos.x \
					+ (1 - plr.step_x) / 2) / plr.ray_dir_x;
		else
			plr.wall_dist = (plr.map_y - new_pos.y \
					+ (1 - plr.step_y) / 2) / plr.ray_dir_y;
		if (plr.wall_dist < data->hitbox && mode != 4)
			return (1);
		else if (mode == 4 && plr.wall_dist < 1 && plr.door_num != -1)
			return (2);
		plr.x += 4;
	}
	return (0);
}
