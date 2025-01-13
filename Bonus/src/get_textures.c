/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:23:38 by pauberna          #+#    #+#             */
/*   Updated: 2025/01/06 18:04:11 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	get_texture(t_data *data, char *texture)
{
	if (ft_isprint(texture[1]) == 0)
		return (1);
	if (!data->north_text && texture[0] == 'N')
		data->north_text = get_texture_path(texture + 2);
	else if (!data->south_text && texture[0] == 'S')
		data->south_text = get_texture_path(texture + 2);
	else if (!data->east_text && texture[0] == 'E')
		data->east_text = get_texture_path(texture + 2);
	else if (!data->west_text && texture[0] == 'W')
		data->west_text = get_texture_path(texture + 2);
	else if (texture[0] == 'N' || texture[0] == 'S' \
		|| texture[0] == 'E' || texture[0] == 'W')
		return (1);
	return (0);
}

char	*get_texture_path(char *str)
{
	int		n;
	char	*path;

	n = 0;
	while (str[n] && ((str[n] >= 9 && str[n] <= 13) || str[n] == ' '))
		n++;
	path = ft_strdup(str + n);
	if (!path)
		return (NULL);
	n = 0;
	while (path[n] && (path[n] < 9 || path[n] > 13) && path[n] != ' ')
		n++;
	path[n] = '\0';
	return (path);
}

int	get_color(char *str)
{
	int	r;
	int	g;
	int	b;
	int	n;
	int	color;

	n = 2;
	while (str[n] && ((str[n] >= 9 && str[n] <= 13) || str[n] == ' '))
		n++;
	r = mini_atoi(str, &n);
	g = mini_atoi(str, &n);
	b = mini_atoi(str, &n);
	if (r == -1 || g == -1 || b == -1)
		return (-1);
	color = (r << 16) + (g << 8) + b;
	return (color);
}

int	mini_atoi(char *str, int *index)
{
	int	n;
	int	nbr;

	nbr = 0;
	n = *index;
	if (str[n] < '0' || str[n] > '9')
		return (-1);
	while (str && str[n] >= '0' && str[n] <= '9')
	{
		nbr = (nbr * 10) + (str[n] - '0');
		n++;
	}
	if (str[n] == ',')
		*index = n + 1;
	else
		*index = n;
	if (nbr < 0 || nbr > 255)
		nbr = -1;
	return (nbr);
}

t_img	*new_file_img(char *path, void *mlx)
{
	t_img	*image;

	image = (t_img *)malloc(sizeof(t_img));
	image->mlx_img = mlx_xpm_file_to_image(mlx, path, &image->width,
			&image->height);
	if (!image->mlx_img)
		return (write(2, "File could not be read\n", 23), NULL);
	else
		image->addr = mlx_get_data_addr(image->mlx_img, \
			&(image->bits_per_pixel), &(image->line_length), &(image->endian));
	return (image);
}
