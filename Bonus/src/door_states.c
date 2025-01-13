/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_states.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:48:16 by pauberna          #+#    #+#             */
/*   Updated: 2025/01/06 18:03:51 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	change_door_states(t_data *data)
{
	int						nbr;
	t_vector				new_pos;

	new_pos.x = data->plr.pos.x + data->plr.cam.dir.x;
	new_pos.y = data->plr.pos.y + data->plr.cam.dir.y;
	nbr = find_door_num(data, (int)new_pos.x, (int)new_pos.y);
	if (nbr >= 0 && open_door_state(data, nbr) == 0)
		close_door_state(data, nbr);
}

int	open_door_state(t_data *data, int nbr)
{
	if (data->door[nbr].open == 1 && data->door[nbr].old_state == 0)
	{
		data->door[nbr].open = 2;
		data->door[nbr].old_state = 1;
		data->move = false;
		return (1);
	}
	else if (data->door[nbr].open == 2 && data->door[nbr].old_state == 1)
	{
		data->door[nbr].open = 3;
		data->door[nbr].old_state = 2;
		return (1);
	}
	else if (data->door[nbr].open == 3 && data->door[nbr].old_state == 2)
	{
		data->door[nbr].open = 4;
		data->door[nbr].old_state = 3;
		data->move = true;
		return (1);
	}
	return (0);
}

void	close_door_state(t_data *data, int nbr)
{
	if (data->door[nbr].open == 3 && data->door[nbr].old_state == 4)
	{
		data->door[nbr].open = 2;
		data->door[nbr].old_state = 3;
		data->move = false;
	}
	else if (data->door[nbr].open == 2 && data->door[nbr].old_state == 3)
	{
		data->door[nbr].open = 1;
		data->door[nbr].old_state = 2;
	}
	else if (data->door[nbr].open == 1 && data->door[nbr].old_state == 2)
	{
		data->door[nbr].open = 0;
		data->door[nbr].old_state = 1;
		data->move = true;
	}
}
