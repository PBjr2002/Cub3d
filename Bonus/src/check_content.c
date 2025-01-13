/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:29:17 by pauberna          #+#    #+#             */
/*   Updated: 2025/01/06 18:03:21 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	check_map_content(t_data *data)
{
	int	n;
	int	i;

	n = 0;
	while (data->map[n])
	{
		i = 0;
		while (data->map[n][i])
		{
			if (data->map[n][i] != ' '
				&& data->map[n][i] != '1' && data->map[n][i] != '0'
				&& data->map[n][i] != 'N' && data->map[n][i] != 'S'
				&& data->map[n][i] != 'E' && data->map[n][i] != 'W'
				&& data->map[n][i] != 'D')
				return (1);
			i++;
		}
		n++;
	}
	return (0);
}

int	check_xpms(t_data *data)
{
	if (check_file(data->north_text, 1) == 1)
		return (1);
	else if (check_file(data->south_text, 1) == 1)
		return (1);
	else if (check_file(data->east_text, 1) == 1)
		return (1);
	else if (check_file(data->west_text, 1) == 1)
		return (1);
	data->n_wall = new_file_img(data->north_text, data->mlx);
	data->s_wall = new_file_img(data->south_text, data->mlx);
	data->e_wall = new_file_img(data->east_text, data->mlx);
	data->w_wall = new_file_img(data->west_text, data->mlx);
	data->door_tex[0] = new_file_img("textures/Door.xpm", data->mlx);
	data->door_tex[1] = new_file_img("textures/Door1.xpm", data->mlx);
	data->door_tex[2] = new_file_img("textures/Door2.xpm", data->mlx);
	data->door_tex[3] = new_file_img("textures/Door3.xpm", data->mlx);
	if (!data->n_wall || !data->s_wall
		|| !data->e_wall || !data->w_wall || !data->door_tex[0]
		|| !data->door_tex[1] || !data->door_tex[2] || !data->door_tex[3])
		return (1);
	return (0);
}
