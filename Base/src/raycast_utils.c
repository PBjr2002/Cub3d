/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 10:26:09 by pauberna          #+#    #+#             */
/*   Updated: 2025/01/06 18:07:24 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_build_sky_floor(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->height / 2)
	{
		x = 0;
		while (x < data->width)
		{
			my_mlx_pixel_put(data, x, y, data->ceiling);
			x++;
		}
		y++;
	}
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			my_mlx_pixel_put(data, x, y, data->floor);
			x++;
		}
		y++;
	}
}

void	render_first_layer(t_data *data)
{
	t_vars	vars;

	vars_init(&vars);
	while (++(vars.x) < data->width)
	{
		set_ray_dir_and_dist(data, &vars);
		set_ray_side_dist(data, &vars);
		set_dist_to_wall(data, &vars, 0);
		set_draw_len(data, &vars);
		while (vars.draw_start <= vars.draw_end)
		{
			vars.pos += vars.step;
			if (vars.side == 0 && vars.ray_dir_x < 0)
				draw_texture(data, data->w_wall, &vars);
			else if (vars.side == 0)
				draw_texture(data, data->e_wall, &vars);
			else if (vars.side == 1 && vars.ray_dir_y < 0)
				draw_texture(data, data->n_wall, &vars);
			else if (vars.side == 1)
				draw_texture(data, data->s_wall, &vars);
			vars.draw_start++;
		}
	}
}
