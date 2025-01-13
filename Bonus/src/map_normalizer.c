/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_normalizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:25:23 by pauberna          #+#    #+#             */
/*   Updated: 2025/01/06 18:04:29 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	map_normalizer(t_data *data, int map_height)
{
	char	**new_map;
	int		n;

	data->column_count = find_width(data->map);
	new_map = ft_calloc(sizeof(char *), map_height + 1);
	n = 0;
	while (data->map[n])
	{
		new_map[n] = resize_line(data->map[n], data->column_count);
		if (!new_map[n])
			return ;
		n++;
	}
	free_dptr(data->map);
	data->map = new_map;
}

char	*resize_line(char *line, int map_width)
{
	char	*new_line;
	int		i;

	new_line = ft_calloc(sizeof(char), map_width + 1);
	if (!new_line)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		new_line[i] = line[i];
		i++;
	}
	while (i < map_width)
	{
		new_line[i] = ' ';
		i++;
	}
	return (new_line);
}

int	find_width(char **map)
{
	int	width;
	int	n;
	int	i;

	width = 0;
	n = 0;
	while (map && map[n])
	{
		i = 0;
		while (map[n][i] && map[n][i] != '\n')
			i++;
		if (i > width)
			width = i;
		n++;
	}
	return (width);
}

int	find_height(char **map)
{
	int	height;

	height = 0;
	while (map[height])
		height++;
	return (height);
}

void	free_dptr(char **dptr)
{
	int	n;

	n = 0;
	while (dptr && dptr[n])
	{
		free(dptr[n]);
		n++;
	}
	if (dptr)
		free(dptr);
	dptr = NULL;
}
