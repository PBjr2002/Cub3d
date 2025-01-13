/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:42:52 by pauberna          #+#    #+#             */
/*   Updated: 2025/01/06 18:04:48 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	ft_move_mouse(t_data *model)
{
	int		new_mouse_x;

	model->old_mouse = model->new_mouse;
	mlx_mouse_get_pos(model->mlx, model->mlx_window, &new_mouse_x, \
		(int *)&model->new_mouse.y);
	if (model->old_mouse.x == new_mouse_x || model->keys[7] == 1)
		return (1);
	if (new_mouse_x > 0 && new_mouse_x < model->width)
	{
		if (model->old_mouse.x - new_mouse_x >= 0)
			ft_mouse_rotation(model, -M_PI * MOUSE_ROT);
		else
			ft_mouse_rotation(model, M_PI * MOUSE_ROT);
		mlx_mouse_move(model->mlx, model->mlx_window, \
			new_mouse_x, W_HEIGHT / 2);
		model->new_mouse.x = new_mouse_x;
	}
	else if (new_mouse_x <= 0 || new_mouse_x >= model->width)
	{
		model->new_mouse.x = W_WIDTH / 2;
		mlx_mouse_move(model->mlx, model->mlx_window, \
			W_WIDTH / 2, W_HEIGHT / 2);
	}
	return (0);
}

void	ft_mouse_rotation(t_data *model, float angle)
{
	float	old_dir_x;
	float	old_plane_x;

	if (model->move == true)
	{
		old_dir_x = model->plr.cam.dir.x;
		old_plane_x = model->plr.cam.plane.x;
		model->plr.cam.dir.x = model->plr.cam.dir.x * cos(angle) - \
			model->plr.cam.dir.y * sin(angle);
		model->plr.cam.dir.y = old_dir_x * sin(angle) + \
			model->plr.cam.dir.y * cos(angle);
		model->plr.cam.plane.x = model->plr.cam.plane.x * cos(angle) - \
			model->plr.cam.plane.y * sin(angle);
		model->plr.cam.plane.y = old_plane_x * sin(angle) + \
			model->plr.cam.plane.y * cos(angle);
	}
}
