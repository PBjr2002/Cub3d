/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:09:48 by pauberna          #+#    #+#             */
/*   Updated: 2025/01/06 18:03:58 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	draw_texture(t_data *data, t_img *img, t_vars *vars)
{
	if (get_pixel_img(img, vars->tex_x, (int)vars->pos) == 0)
	{
		vars->pos -= vars->step;
		my_mlx_pixel_put(data, vars->x, vars->draw_start,
			get_pixel_img(img, vars->tex_x, (int)vars->pos));
	}
	else
		my_mlx_pixel_put(data, vars->x, vars->draw_start,
			get_pixel_img(img, vars->tex_x, (int)vars->pos));
}

unsigned int	get_pixel_img(t_img *img, int x, int y)
{
	return (*(unsigned int *)((img->addr
			+ (y * img->line_length) + (x * img->bits_per_pixel / 8))));
}

void	my_mlx_pixel_put(t_data *model, int x, int y, int color)
{
	char	*dst;

	if (color == 0xFFFFFF)
		return ;
	if (x >= 0 && y >= 0 && x < model->width && y < model->height)
	{
		dst = model->img.addr + (y * model->img.line_length
				+ x * (model->img.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	ft_creat_image(t_data *model, int x, int y)
{
	model->img.mlx_img = mlx_new_image(model->mlx, x, y);
	model->img.addr = mlx_get_data_addr(model->img.mlx_img,
			&model->img.bits_per_pixel, &model->img.line_length,
			&model->img.endian);
}
