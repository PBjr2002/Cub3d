/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:14:39 by pauberna          #+#    #+#             */
/*   Updated: 2025/01/06 18:04:01 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	free_data(t_data *data)
{
	free(data->timeval);
	if (data->file_name)
		free(data->file_name);
	if (data->map)
		free_dptr(data->map);
	if (data->og_map)
		free_dptr(data->og_map);
	free_imgs(data);
	free_text(data);
	if (data->mini_plr)
		free(data->mini_plr);
	if (data->door)
		free(data->door);
	if (data->img.mlx_img)
		mlx_destroy_image(data->mlx, data->img.mlx_img);
	if (data->mlx_window)
	{
		mlx_destroy_window(data->mlx, data->mlx_window);
		mlx_destroy_display(data->mlx);
	}
	if (data->mlx)
		free(data->mlx);
}

void	free_text(t_data *data)
{
	if (data->north_text)
		free(data->north_text);
	if (data->south_text)
		free(data->south_text);
	if (data->east_text)
		free(data->east_text);
	if (data->west_text)
		free(data->west_text);
}

void	free_imgs(t_data *data)
{
	if (data->n_wall)
	{
		mlx_destroy_image(data->mlx, data->n_wall->mlx_img);
		free(data->n_wall);
	}
	if (data->s_wall)
	{
		mlx_destroy_image(data->mlx, data->s_wall->mlx_img);
		free(data->s_wall);
	}
	if (data->e_wall)
	{
		mlx_destroy_image(data->mlx, data->e_wall->mlx_img);
		free(data->e_wall);
	}
	if (data->w_wall)
	{
		mlx_destroy_image(data->mlx, data->w_wall->mlx_img);
		free(data->w_wall);
	}
	free_door(data);
}

void	free_door(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->door_tex[i])
		{
			mlx_destroy_image(data->mlx, data->door_tex[i]->mlx_img);
			free(data->door_tex[i]);
		}
		i++;
	}
}

void	verify_elements(t_data *data, int flag)
{
	if (data->floor == -1 || data->ceiling == -1
		|| !data->north_text || !data->south_text
		|| !data->east_text || !data->west_text)
	{
		free_dptr(data->map);
		data->map = NULL;
	}
	else if (flag == 3)
	{
		if (data->north_text)
			free(data->north_text);
		data->north_text = NULL;
		if (data->south_text)
			free(data->south_text);
		data->south_text = NULL;
		if (data->east_text)
			free(data->east_text);
		data->east_text = NULL;
		if (data->west_text)
			free(data->west_text);
		data->west_text = NULL;
	}
}
