/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:08:49 by pauberna          #+#    #+#             */
/*   Updated: 2025/01/06 18:07:00 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_key_push(int keycode, t_data *model)
{
	if (keycode == ESC_KEY)
		ft_close_window(model);
	else if (keycode == W_KEY && model->move == true)
		model->keys[0] = 1;
	else if (keycode == S_KEY && model->move == true)
		model->keys[1] = 1;
	else if (keycode == A_KEY && model->move == true)
		model->keys[2] = 1;
	else if (keycode == D_KEY && model->move == true)
		model->keys[3] = 1;
	else if (keycode == L_ARR_KEY && model->move == true)
		model->keys[4] = 1;
	else if (keycode == R_ARR_KEY && model->move == true)
		model->keys[5] = 1;
	return (0);
}

int	ft_key_release(int keycode, t_data *model)
{
	if (keycode == W_KEY && model->keys[0] == 1)
		model->keys[0] = 0;
	else if (keycode == S_KEY && model->keys[1] == 1)
		model->keys[1] = 0;
	else if (keycode == A_KEY && model->keys[2] == 1)
		model->keys[2] = 0;
	else if (keycode == D_KEY && model->keys[3] == 1)
		model->keys[3] = 0;
	else if (keycode == L_ARR_KEY && model->keys[4] == 1)
		model->keys[4] = 0;
	else if (keycode == R_ARR_KEY && model->keys[5] == 1)
		model->keys[5] = 0;
	return (0);
}

void	key_check1(t_data *data)
{
	if (data->keys[0] == 1)
	{
		if (is_there_a_wall(data, 0) == 1)
			return ;
		data->plr.pos.x += data->plr.cam.dir.x * MOVE_SPEED;
		data->plr.pos.y += data->plr.cam.dir.y * MOVE_SPEED;
	}
	else if (data->keys[1] == 1)
	{
		if (is_there_a_wall(data, 1) == 1)
			return ;
		data->plr.pos.x -= data->plr.cam.dir.x * MOVE_SPEED;
		data->plr.pos.y -= data->plr.cam.dir.y * MOVE_SPEED;
	}
}

void	key_check2(t_data *data)
{
	if (data->keys[2] == 1)
	{
		if (is_there_a_wall(data, 2) == 1)
			return ;
		data->plr.pos.x += data->plr.cam.dir.y * MOVE_SPEED;
		data->plr.pos.y -= data->plr.cam.dir.x * MOVE_SPEED;
	}
	else if (data->keys[3] == 1)
	{
		if (is_there_a_wall(data, 3) == 1)
			return ;
		data->plr.pos.x -= data->plr.cam.dir.y * MOVE_SPEED;
		data->plr.pos.y += data->plr.cam.dir.x * MOVE_SPEED;
	}
}

void	ft_rotation(t_data *model, float value)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = model->plr.cam.dir.x;
	old_plane_x = model->plr.cam.plane.x;
	model->plr.cam.dir.x = model->plr.cam.dir.x * cos(value) \
		- model->plr.cam.dir.y * sin(value);
	model->plr.cam.dir.y = old_dir_x * sin(value) \
		+ model->plr.cam.dir.y * cos(value);
	model->plr.cam.plane.x = model->plr.cam.plane.x * cos(value) \
		- model->plr.cam.plane.y * sin(value);
	model->plr.cam.plane.y = old_plane_x * sin(value) \
		+ model->plr.cam.plane.y * cos(value);
}
