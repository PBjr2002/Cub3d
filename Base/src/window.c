/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:34:21 by pauberna          #+#    #+#             */
/*   Updated: 2025/01/06 18:07:33 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_close_window(t_data *model)
{
	free_data(model);
	exit (0);
}

void	ft_creat_window(t_data *model)
{
	model->mlx = mlx_init();
	model->mlx_window = mlx_new_window(model->mlx, model->width,
			model->height, "Cub3D");
	ft_creat_image(model, model->width, model->height);
}

int	render(void *src)
{
	t_data					*data;

	data = (t_data *)src;
	gettimeofday((struct timeval *)data->timeval, NULL);
	if ((data->timeval->tv_sec * 1000000 + \
	data->timeval->tv_usec) > data->frame)
	{
		ft_build_image(data);
		mlx_put_image_to_window(data->mlx, data->mlx_window,
			data->img.mlx_img, 0, 0);
		gettimeofday((struct timeval *)data->timeval, NULL);
		data->frame = data->timeval->tv_sec * 1000000 \
		+ data->timeval->tv_usec + (1000000 / FRAME_R);
	}
	return (0);
}
