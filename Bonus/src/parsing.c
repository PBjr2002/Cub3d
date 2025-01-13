/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:34:23 by pauberna          #+#    #+#             */
/*   Updated: 2025/01/06 18:04:56 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	check_file_name(char *map_name, char *str)
{
	int	len;

	if (map_name == NULL)
		return (1);
	len = ft_strlen(map_name);
	if (len < 5)
		return (1);
	if (ft_strncmp(map_name + len - ft_strlen(str), \
		str, len - ft_strlen(str)) != 0)
		return (1);
	return (0);
}

int	check_file(char *file, int mode)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	if (mode == 0 && check_file_name(file, ".cub") == 1)
		return (1);
	if (mode == 1 && check_file_name(file, ".xpm") == -1)
		return (1);
	return (0);
}

int	map_lines_counter(char *map)
{
	char	*str;
	int		n;
	int		fd;

	fd = open(map, O_RDONLY);
	n = 1;
	str = ft_get_next_line(fd);
	while (str)
	{
		free(str);
		str = ft_get_next_line(fd);
		n++;
	}
	close(fd);
	return (n);
}

void	set_data(t_data *data, char *file)
{
	int	lines;
	int	n;

	lines = map_lines_counter(file);
	data->og_map = ft_calloc(sizeof(char *), lines + 1);
	data->file_name = ft_strdup(file);
	data->fd = open(file, O_RDONLY);
	if (data->fd == -1)
		return ;
	n = 0;
	while (n < lines)
	{
		data->og_map[n] = ft_get_next_line(data->fd);
		n++;
	}
	close(data->fd);
}

int	parsing(t_data *data, char *file)
{
	if (check_file(file, 0) == 1)
		return (1);
	set_data(data, file);
	get_map_info(data);
	if (!data->map)
		return (1);
	return (0);
}
