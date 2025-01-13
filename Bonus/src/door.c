/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:04:40 by pauberna          #+#    #+#             */
/*   Updated: 2025/01/06 18:03:55 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	get_door_info(t_data *data, char **map)
{
	int	n;
	int	i;
	int	counter;

	n = 0;
	counter = 0;
	data->door = ft_calloc(sizeof(t_door), data->door_num);
	while (map[n])
	{
		i = 0;
		while (map[n][i])
		{
			if (map[n][i] == 'D')
			{
				data->door[counter].pos.x = i;
				data->door[counter].pos.y = n;
				data->door->open = 0;
				data->door->old_state = 5;
				counter++;
			}
			i++;
		}
		n++;
	}
}

int	find_door_num(t_data *data, int x, int y)
{
	int	nbr;

	nbr = 0;
	while (nbr < data->door_num)
	{
		if (x == data->door[nbr].pos.x && y == data->door[nbr].pos.y)
			return (nbr);
		nbr++;
	}
	return (-1);
}

void	open_door(t_data *data)
{
	int			nbr;
	t_vector	new_pos;

	nbr = 0;
	new_pos.x = data->plr.pos.x + data->plr.cam.dir.x;
	new_pos.y = data->plr.pos.y + data->plr.cam.dir.y;
	if (check_move(data, data->plr.pos, 4) == 2)
	{
		nbr = find_door_num(data, (int)new_pos.x, (int)new_pos.y);
		if (nbr != -1)
		{
			if (data->door[nbr].open == 4)
			{
				data->door[nbr].open = 3;
				data->door[nbr].old_state = 4;
			}
			else if (data->door[nbr].open == 0)
			{
				data->door[nbr].open = 1;
				data->door[nbr].old_state = 0;
			}
		}
	}
}

int	check_if_open_door(t_data *data, t_check *plr)
{
	if (data->map[plr->map_y][plr->map_x] == '1' \
		|| data->map[plr->map_y][plr->map_x] == 'D')
	{
		if (data->map[plr->map_y][plr->map_x] == 'D')
		{
			plr->door_num = find_door_num(data, plr->map_x, plr->map_y);
			if (data->door[plr->door_num].open == 0)
				return (1);
		}
		else
			return (1);
	}
	return (0);
}
