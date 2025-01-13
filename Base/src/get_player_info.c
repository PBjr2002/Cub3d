/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:19:54 by pauberna          #+#    #+#             */
/*   Updated: 2025/01/06 18:06:51 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	player_init(t_plr *plr)
{
	plr->cam.dir.x = 0;
	plr->cam.dir.y = 0;
	plr->cam.plane.x = 0;
	plr->cam.plane.y = 0;
	plr->pos.x = 0;
	plr->pos.y = 0;
}

void	set_player_direction(t_data *data)
{
	if (data->map[(int)data->plr.pos.y][(int)data->plr.pos.x] == 'N'
		|| data->map[(int)data->plr.pos.y][(int)data->plr.pos.x] == 'S'
		|| data->map[(int)data->plr.pos.y][(int)data->plr.pos.x] == 'E'
		|| data->map[(int)data->plr.pos.y][(int)data->plr.pos.x] == 'W')
	{
		data->plr.cam.dir.x = 1;
		data->plr.cam.dir.y = 0;
		if (data->map[(int)data->plr.pos.y][(int)data->plr.pos.x] == 'N')
			set_player_dir(data, 0, -1);
		else if (data->map[(int)data->plr.pos.y][(int)data->plr.pos.x] == 'S')
			set_player_dir(data, 0, 1);
		else if (data->map[(int)data->plr.pos.y][(int)data->plr.pos.x] == 'E')
			set_player_dir(data, 1, 0);
		else
			set_player_dir(data, -1, 0);
	}
}

void	get_player_info(t_data *data)
{
	player_init(&data->plr);
	while (data->map[(int)data->plr.pos.y])
	{
		data->plr.pos.x = 0;
		while (data->map[(int)data->plr.pos.y][(int)data->plr.pos.x])
		{
			if (data->map[(int)data->plr.pos.y][(int)data->plr.pos.x] == 'N'
				|| data->map[(int)data->plr.pos.y][(int)data->plr.pos.x] == 'S'
				|| data->map[(int)data->plr.pos.y][(int)data->plr.pos.x] == 'E'
				|| data->map[(int)data->plr.pos.y][(int)data->plr.pos.x] == 'W')
			{
				data->plr.cam.plane.x = 0;
				data->plr.cam.plane.y = 0.66;
				break ;
			}
			data->plr.pos.x++;
		}
		if (data->map[(int)data->plr.pos.y][(int)data->plr.pos.x])
			break ;
		data->plr.pos.y++;
	}
	set_player_direction(data);
	data->plr.pos.x += 0.5;
	data->plr.pos.y += 0.5;
	data->hitbox = 0.25;
}

void	set_player_dir(t_data *data, float target_x, float target_y)
{
	if (target_x != 0 && data->plr.cam.dir.x != target_x)
	{
		while (target_x != data->plr.cam.dir.x)
			ft_rotation(data, M_PI / 2);
	}
	else if (target_y != 0 && data->plr.cam.dir.y != target_y)
	{
		while (target_y != data->plr.cam.dir.y)
			ft_rotation(data, M_PI / 2);
	}
}
