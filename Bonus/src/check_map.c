/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:58:58 by adimas-d          #+#    #+#             */
/*   Updated: 2025/01/06 18:03:38 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	check_for_player(t_data *data)
{
	int	n;
	int	i;
	int	p_nbr;

	n = 0;
	p_nbr = 0;
	while (data->map && data->map[n])
	{
		i = 0;
		while (data->map[n][i])
		{
			if (data->map[n][i] == 'N' || data->map[n][i] == 'S'
				|| data->map[n][i] == 'E' || data->map[n][i] == 'W')
				p_nbr++;
			else if (data->map[n][i] == 'D')
				data->door_num++;
			i++;
		}
		n++;
	}
	if (p_nbr != 1)
		return (1);
	return (0);
}

int	check_top_bottom(char **map, int line_c)
{
	int	n;

	n = 0;
	if (!map)
		return (1);
	while (map[0][n]
			&& (map[0][n] == ' ' || map[0][n] == '1'))
	{
		if (map[0][n] == ' ' && map[1][n] == '0')
			return (1);
		n++;
	}
	if (map[0][n])
		return (1);
	n = 0;
	while (map[line_c - 1][n] && (map[line_c - 1][n] == ' '
			|| map[line_c - 1][n] == '1'))
	{
		if (map[line_c - 1][n] == ' ' && map[line_c - 2][n] == '0')
			return (1);
		n++;
	}
	if (map[line_c - 1][n])
		return (1);
	return (0);
}

int	check_left_right(char **map, int column_c)
{
	int	n;

	n = 0;
	if (!map)
		return (1);
	while (map[n] && map[n][0]
			&& (map[n][0] == ' ' || map[n][0] == '1'))
	{
		if (map[n][0] == ' ' && map[n][1] == '0')
			return (1);
		n++;
	}
	if (map[n] && map[n][0])
		return (1);
	n = 0;
	while (map[n] && map[n][column_c - 1] && (map[n][column_c - 1] == ' '
			|| map[n][column_c - 1] == '1'))
	{
		if (map[n][column_c - 1] == ' ' && map[n][column_c - 2] == '0')
			return (1);
		n++;
	}
	if (map[n] && map[n][column_c - 1])
		return (1);
	return (0);
}

int	check_middle(char **map)
{
	int	n;
	int	i;

	n = 1;
	if (!map)
		return (1);
	while (map[n + 1])
	{
		i = 1;
		while (map[n + 1][i + 1])
		{
			if (map[n][i] == ' ')
			{
				if ((map[n][i + 1] != ' ' && map[n][i + 1] != '1')
					|| (map[n][i - 1] != ' ' && map[n][i - 1] != '1')
					|| (map[n + 1][i] != ' ' && map[n + 1][i] != '1')
					|| (map[n - 1][i] != ' ' && map[n - 1][i] != '1'))
					return (1);
			}
			i++;
		}
		n++;
	}
	return (0);
}

int	check_walls(t_data *data)
{
	if (check_top_bottom(data->map, data->line_count) == 1
		|| check_left_right(data->map, data->column_count) == 1
		|| check_middle(data->map) == 1)
		return (1);
	get_door_info(data, data->map);
	return (0);
}
