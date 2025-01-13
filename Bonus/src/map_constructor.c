/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_constructor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:19:59 by pauberna          #+#    #+#             */
/*   Updated: 2025/01/06 18:04:27 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	construct_map(t_data *data, int n)
{
	int	i;

	data->line_count = get_map_height(data->og_map, n);
	data->map = ft_calloc(sizeof(char *), data->line_count + 1);
	i = 0;
	while (i < data->line_count)
	{
		data->map[i] = ft_strdup(data->og_map[n]);
		n++;
		i++;
	}
	map_normalizer(data, data->line_count);
	if (check_for_player(data) == 1 || check_walls(data) == 1
		|| check_map_content(data) == 1)
	{
		free_dptr(data->map);
		data->map = NULL;
	}
	else
		get_player_info(data);
}

void	get_map_info(t_data *data)
{
	int	n;
	int	i;
	int	flag;

	n = 0;
	while (data->og_map[n])
	{
		i = 0;
		while (data->og_map[n] && data->og_map[n][i] \
			&& ft_strncmp(data->og_map[n], "\n", 1) == 0)
			n++;
		while (data->og_map[n] && data->og_map[n][i])
		{
			flag = get_dptr_info(data, n, &i);
			if (flag == 1 || flag == 3)
			{
				verify_elements(data, flag);
				return ;
			}
			else if (flag == 2)
				break ;
			i++;
		}
		n++;
	}
}

int	get_dptr_info(t_data *data, int n, int *i)
{
	while (data->og_map[n][*i]
		&& ((data->og_map[n][*i] >= 9 && data->og_map[n][*i] <= 13)
		|| data->og_map[n][*i] == ' '))
		(*i)++;
	if (ft_isdigit(data->og_map[n][*i]) == 0
		&& ft_isprint(data->og_map[n][*i]) == 1 && data->og_map[n][*i + 1])
	{
		if (texture_storage(data, n, *i) == 1)
			return (3);
		return (2);
	}
	else if (ft_isdigit(data->og_map[n][*i]) == 0 || data->og_map[n][*i] == ' ')
		return (construct_map(data, n), \
			free_dptr(data->og_map), data->og_map = NULL, 1);
	return (0);
}

int	texture_storage(t_data *data, int n, int i)
{
	if (data->og_map[n][i] != 'F' && data->og_map[n][i] != 'C')
	{
		if (get_texture(data, data->og_map[n] + i) == 1)
			return (1);
	}
	else if (data->floor == -1 && data->og_map[n][i] == 'F')
		data->floor = get_color(data->og_map[n] + i);
	else if (data->ceiling == -1 && data->og_map[n][i] == 'C')
		data->ceiling = get_color(data->og_map[n] + i);
	else if (data->og_map[n][i] == 'F' || data->og_map[n][i] == 'C')
		return (1);
	return (0);
}

int	get_map_height(char **map, int n)
{
	int	height;

	height = 0;
	while (map && map[n])
	{
		map++;
		height++;
	}
	return (height);
}
